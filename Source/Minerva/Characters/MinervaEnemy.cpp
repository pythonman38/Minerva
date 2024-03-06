// Midnight Madness Inc.


#include "MinervaEnemy.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Minerva/AbilitySystem/MinervaAbilitySystemComponent.h"
#include "Minerva/AbilitySystem/MinervaAttributeSet.h"
#include "Minerva/AbilitySystem/MinervaAbilitySystemLibrary.h"
#include "Minerva/AI/MinervaAIController.h"
#include "Minerva/HUD/MinervaUserWidget.h"
#include "Minerva/Minerva.h"
#include "Minerva/Singletons/MinervaGameplayTags.h"

AMinervaEnemy::AMinervaEnemy() :
	Level(1),
	CharacterClass(ECharacterClass::Warrior),
	bHitReacting(false),
	BaseWalkSpeed(250.f),
	LifeSpan(5.f)
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UMinervaAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	AttributeSet = CreateDefaultSubobject<UMinervaAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AMinervaEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	MinervaAIController = Cast<AMinervaAIController>(NewController);

	MinervaAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	MinervaAIController->RunBehaviorTree(BehaviorTree);
	MinervaAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	MinervaAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), CharacterClass != ECharacterClass::Warrior);
}

void AMinervaEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AMinervaEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AMinervaEnemy::GetPlayerLevel()
{
	return Level;
}

void AMinervaEnemy::Die()
{
	SetLifeSpan(LifeSpan);

	Super::Die();
}

void AMinervaEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	MinervaAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
}

void AMinervaEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();

	SetEnemyWidgetController();
}

void AMinervaEnemy::SetEnemyWidgetController()
{
	if (auto MinervaUserWidget = Cast<UMinervaUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		MinervaUserWidget->SetWidgetController(this);
	}

	if (const auto MinervaAS = CastChecked<UMinervaAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MinervaAS->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) { OnHealthChanged.Broadcast(Data.NewValue); });
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MinervaAS->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) { OnMaxHealthChanged.Broadcast(Data.NewValue); });
		AbilitySystemComponent->RegisterGameplayTagEvent(FMinervaGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AMinervaEnemy::HitReactTagChanged);

		OnHealthChanged.Broadcast(MinervaAS->GetHealth());
		OnMaxHealthChanged.Broadcast(MinervaAS->GetMaxHealth());
	}
}

void AMinervaEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UMinervaAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (HasAuthority())
	{
		InitializeDefaultAttributes();

		UMinervaAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
	}
	
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
}

void AMinervaEnemy::InitializeDefaultAttributes() const
{
	UMinervaAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
