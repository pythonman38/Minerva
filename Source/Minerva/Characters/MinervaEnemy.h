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

protected:
	virtual void BeginPlay() override;
};
