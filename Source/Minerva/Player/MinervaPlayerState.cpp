// Midnight Madness Inc.


#include "MinervaPlayerState.h"

#include "Minerva/AbilitySystem/MinervaAbilitySystemComponent.h"
#include "Minerva/AbilitySystem/MinervaAttributeSet.h"

AMinervaPlayerState::AMinervaPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMinervaAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMinervaAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AMinervaPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
