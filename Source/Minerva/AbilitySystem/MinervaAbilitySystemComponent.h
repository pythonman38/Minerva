// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MinervaAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*Asset Tags*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGiven, UMinervaAbilitySystemComponent*);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);

UCLASS()
class MINERVA_API UMinervaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);

	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ForEachAbility(const FForEachAbility& Delegate);

	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

public:
	bool bStartupAbilitiesGiven = false;

	FEffectAssetTags EffectAssetTags;

	FAbilitiesGiven AbilitiesGivenDelegate;
	
protected:
	virtual void OnRep_ActivateAbilities() override;

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
