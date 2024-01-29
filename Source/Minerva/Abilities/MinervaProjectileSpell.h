// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "MinervaDamageGameplayAbility.h"
#include "MinervaProjectileSpell.generated.h"

class AMinervaProjectile;
class UGameplayEffect;

UCLASS()
class MINERVA_API UMinervaProjectileSpell : public UMinervaDamageGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData);

	UFUNCTION(BlueprintCallable, Category = Projectile)
	void SpawnProjectile(const FVector& ProjectileTargetLocation);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = true))
	TSubclassOf<AMinervaProjectile> ProjectileClass;
};
