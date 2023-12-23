// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "MinervaCharacterBase.h"
#include "Minerva/Interaction/EnemyInterface.h"
#include "MinervaEnemy.generated.h"

UCLASS()
class MINERVA_API AMinervaEnemy : public AMinervaCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AMinervaEnemy();

	// Inherited via IEnemyInterface
	void HighlightActor() override;
	void UnHighlightActor() override;

	// Inherited via ICombatInterface
	virtual int32 GetPlayerLevel() override;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults", meta = (AllowPrivateAccess = "true"))
	int32 Level;
};
