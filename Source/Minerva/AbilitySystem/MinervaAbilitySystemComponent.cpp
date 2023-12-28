// Midnight Madness Inc.


#include "MinervaAbilitySystemComponent.h"

#include "Minerva/Singletons/MinervaGameplayTags.h"

void UMinervaAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UMinervaAbilitySystemComponent::EffectApplied);
}

void UMinervaAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}
