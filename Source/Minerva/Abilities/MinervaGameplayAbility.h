// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MinervaGameplayAbility.generated.h"

struct FGameplayTag;

UCLASS()
class MINERVA_API UMinervaGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	FGameplayTag StartupInputTag;
};
