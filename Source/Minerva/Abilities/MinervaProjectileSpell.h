// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "MinervaGameplayAbility.h"
#include "MinervaProjectileSpell.generated.h"

class AMinervaProjectile;

UCLASS()
class MINERVA_API UMinervaProjectileSpell : public UMinervaGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMinervaProjectile> ProjectileClass;
};
