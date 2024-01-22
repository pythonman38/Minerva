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
	virtual void Die() override;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = Combat)
	bool bHitReacting;

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
	float BaseWalkSpeed, LifeSpan;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults", meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults", meta = (AllowPrivateAccess = true))
	ECharacterClass CharacterClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widgets, meta = (AllowPrivateAccess = true))
	TObjectPtr<UWidgetComponent> HealthBar;
};
