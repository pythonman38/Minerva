// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "MinervaGameplayAbility.h"
#include "MinervaDamageGameplayAbility.generated.h"


UCLASS()
class MINERVA_API UMinervaDamageGameplayAbility : public UMinervaGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = Damage)
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
