// Midnight Madness Inc.


#include "MinervaAbilitySystemGlobals.h"

#include "Minerva/AbilitySystem/MinervaAbilityTypes.h"

FGameplayEffectContext* UMinervaAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FMinervaGameplayEffectContext();
}
