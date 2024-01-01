// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MinervaGameModeBase.generated.h"

class UCharacterClassInfo;

UCLASS()
class MINERVA_API AMinervaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CharacterClassDefaults)
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
