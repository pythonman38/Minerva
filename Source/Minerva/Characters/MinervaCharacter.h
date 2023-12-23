// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "MinervaCharacterBase.h"
#include "MinervaCharacter.generated.h"

UCLASS()
class MINERVA_API AMinervaCharacter : public AMinervaCharacterBase
{
	GENERATED_BODY()
	
public:
	AMinervaCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	// Inherited via ICombatInterface
	virtual int32 GetPlayerLevel() override;

protected:
	virtual void InitAbilityActorInfo() override;
};
