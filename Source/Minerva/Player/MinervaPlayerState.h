// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "MinervaPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class ULevelUpInfo;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*Stat Value*/)

UCLASS()
class MINERVA_API AMinervaPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AMinervaPlayerState();

	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnPlayerStatChanged OnLevelChangedDelegate;
	FOnPlayerStatChanged OnAttributePointsChangedDelegate;
	FOnPlayerStatChanged OnSpellPointsChangedDelegate;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void AddToXP(int32 InXP);

	void AddToLevel(int32 InLevel);

	void AddToAtributePoints(int32 InPoints);

	void AddToSpellPoints(int32 InPoints);

	void SetXP(int32 InXP);

	void SetLevel(int32 InLevel);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;

protected:
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_XP(int32 OldXP);

	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints);

	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpellPoints);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Level, ReplicatedUsing = OnRep_Level, meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Level, ReplicatedUsing = OnRep_XP, meta = (AllowPrivateAccess = true))
	int32 XP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Level, ReplicatedUsing = OnRep_AttributePoints, meta = (AllowPrivateAccess = true))
	int32 AttributePoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Level, ReplicatedUsing = OnRep_SpellPoints, meta = (AllowPrivateAccess = true))
	int32 SpellPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	// Inherited via IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Getters for private variables
	FORCEINLINE int32 GetAttributePoints() const { return AttributePoints; }
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE int32 GetSpellPoints() const { return SpellPoints; }
	FORCEINLINE int32 GetXP() const { return XP; }
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
};
