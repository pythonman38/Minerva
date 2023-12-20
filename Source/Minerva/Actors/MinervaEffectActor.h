// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MinervaEffectActor.generated.h"

class USphereComponent;

UCLASS()
class MINERVA_API AMinervaEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMinervaEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> Sphere;
};
