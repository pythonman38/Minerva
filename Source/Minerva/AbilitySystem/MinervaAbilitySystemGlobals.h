// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "MinervaAbilitySystemGlobals.generated.h"

UCLASS()
class MINERVA_API UMinervaAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	
public:
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
