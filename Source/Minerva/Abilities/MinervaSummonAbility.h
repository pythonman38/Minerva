// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "MinervaGameplayAbility.h"
#include "MinervaSummonAbility.generated.h"


UCLASS()
class MINERVA_API UMinervaSummonAbility : public UMinervaGameplayAbility
{
	GENERATED_BODY()

public:
	UMinervaSummonAbility();

	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

protected:
	UFUNCTION(BlueprintPure, Category = Summoning)
	TSubclassOf<APawn> GetRandomMinionClass();

private:
	UPROPERTY(EditDefaultsOnly, Category = Summoning, meta = (AllowPrivateAccess = true))
	float SpawnSpread;

	UPROPERTY(EditDefaultsOnly, Category = Summoning, meta = (AllowPrivateAccess = true))
	int32 NumMinions;

	UPROPERTY(EditDefaultsOnly, Category = Summoning, meta = (AllowPrivateAccess = true))
	FVector2D SpawnDistance;

	UPROPERTY(EditDefaultsOnly, Category = Summoning, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<APawn>> MinionClasses;
};
