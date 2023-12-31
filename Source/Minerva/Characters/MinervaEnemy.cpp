// Midnight Madness Inc.


#include "MinervaEnemy.h"

#include "Components/WidgetComponent.h"
#include "Minerva/AbilitySystem/MinervaAbilitySystemComponent.h"
#include "Minerva/AbilitySystem/MinervaAttributeSet.h"
#include "Minerva/HUD/MinervaUserWidget.h"
#include "Minerva/Minerva.h"

AMinervaEnemy::AMinervaEnemy() :
	Level(1)
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UMinervaAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UMinervaAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
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

		OnHealthChanged.Broadcast(MinervaAS->GetHealth());
		OnMaxHealthChanged.Broadcast(MinervaAS->GetMaxHealth());
	}
}

void AMinervaEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UMinervaAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}
