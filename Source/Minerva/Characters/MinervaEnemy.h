// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "MinervaCharacterBase.h"
#include "Minerva/Interaction/EnemyInterface.h"
#include "Minerva/HUD/OverlayWidgetController.h"
#include "Minerva/AbilitySystem/CharacterClassInfo.h"
#include "MinervaEnemy.generated.h"

class AMinervaAIController;
class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class MINERVA_API AMinervaEnemy : public AMinervaCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AMinervaEnemy();

	virtual void PossessedBy(AController* NewController) override;

	// Inherited via IEnemyInterface
	void HighlightActor() override;
	void UnHighlightActor() override;
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget);
	virtual AActor* GetCombatTarget_Implementation() const;

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

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	TObjectPtr<AActor> CombatTarget;

protected:
	virtual void BeginPlay() override;

	void SetEnemyWidgetController();

	virtual void InitAbilityActorInfo() override;

	virtual void InitializeDefaultAttributes() const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = true))
	float BaseWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = true))
	float LifeSpan;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults", meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults", meta = (AllowPrivateAccess = true))
	ECharacterClass CharacterClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widgets, meta = (AllowPrivateAccess = true))
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = true))
	TObjectPtr<AMinervaAIController> MinervaAIController;
};
