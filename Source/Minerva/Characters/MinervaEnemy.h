// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "MinervaCharacterBase.h"
#include "Minerva/Interaction/EnemyInterface.h"
#include "Minerva/HUD/OverlayWidgetController.h"
#include "Minerva/AbilitySystem/CharacterClassInfo.h"
#include "MinervaEnemy.generated.h"

class UWidgetComponent;

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

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:
	virtual void BeginPlay() override;

	void SetEnemyWidgetController();

	virtual void InitAbilityActorInfo() override;

	virtual void InitializeDefaultAttributes() const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults", meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults", meta = (AllowPrivateAccess = true))
	ECharacterClass CharacterClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widgets, meta = (AllowPrivateAccess = true))
	TObjectPtr<UWidgetComponent> HealthBar;
};
