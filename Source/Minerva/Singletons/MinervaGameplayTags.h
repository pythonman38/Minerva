// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/*
* Minerva Gameplay Tags
*
* Singleton containing native Gameplay Tags
*/

struct FMinervaGameplayTags
{
public:
	static const FMinervaGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeGameplayTags();
protected:

private:
	static FMinervaGameplayTags GameplayTags;

public:
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
};