// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MinervaCharacterBase.generated.h"

UCLASS(Abstract)
class MINERVA_API AMinervaCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMinervaCharacterBase();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
