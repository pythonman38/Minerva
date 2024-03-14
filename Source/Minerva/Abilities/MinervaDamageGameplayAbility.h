// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "MinervaGameplayAbility.h"
#include "MinervaDamageGameplayAbility.generated.h"

struct FTaggedMontage;

UCLASS()
class MINERVA_API UMinervaDamageGameplayAbility : public UMinervaGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = Damage)
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
