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

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	// Inherited via IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Getters for private variables
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
};
