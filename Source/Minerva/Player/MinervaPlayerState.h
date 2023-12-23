// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "MinervaPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class MINERVA_API AMinervaPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AMinervaPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Level, ReplicatedUsing = OnRep_Level, meta = (AllowPrivateAccess = "true"))
	int32 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	// Inherited via IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Getters for private variables
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
};
