// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "MinervaProjectile.generated.h"

class UNiagaraSystem;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class MINERVA_API AMinervaProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AMinervaProjectile();

	virtual void Destroyed() override;

public:
	UPROPERTY(BlueprintReadWrite, Category = Projectile, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpceHandle;

protected:
	virtual void BeginPlay() override;

	void SetFireboltProperties();

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	bool bHit;

	float LifeSpan;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = true))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = true))
	TObjectPtr<USoundBase> LoopingSound;

	UPROPERTY(BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAudioComponent> LoopingSoundComponent;
};
