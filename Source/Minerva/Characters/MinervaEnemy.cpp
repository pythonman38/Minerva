// Midnight Madness Inc.


#include "MinervaEnemy.h"

#include "Minerva/AbilitySystem/MinervaAbilitySystemComponent.h"
#include "Minerva/AbilitySystem/MinervaAttributeSet.h"
#include "Minerva/Minerva.h"

AMinervaEnemy::AMinervaEnemy() :
	Level(1)
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UMinervaAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UMinervaAttributeSet>("AttributeSet");
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
}

void AMinervaEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UMinervaAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
