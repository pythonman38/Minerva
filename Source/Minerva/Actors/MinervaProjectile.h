// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MinervaProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class MINERVA_API AMinervaProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AMinervaProjectile();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
};
