// Midnight Madness Inc.


#include "MinervaPlayerState.h"

#include "Minerva/AbilitySystem/MinervaAbilitySystemComponent.h"
#include "Minerva/AbilitySystem/MinervaAttributeSet.h"
#include "Net/UnrealNetwork.h"

AMinervaPlayerState::AMinervaPlayerState() :
	Level(1)
{
	AbilitySystemComponent = CreateDefaultSubobject<UMinervaAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMinervaAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void AMinervaPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMinervaPlayerState, Level);
}

void AMinervaPlayerState::OnRep_Level(int32 OldLevel)
{
}

UAbilitySystemComponent* AMinervaPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
