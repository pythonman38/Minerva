// Midnight Madness Inc.


#include "MinervaAttributeSet.h"

#include "Net/UnrealNetwork.h"

UMinervaAttributeSet::UMinervaAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(50.f);
}

void UMinervaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMinervaAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMinervaAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMinervaAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMinervaAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UMinervaAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMinervaAttributeSet, Health, OldHealth);
}

void UMinervaAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMinervaAttributeSet, MaxHealth, OldMaxHealth);
}

void UMinervaAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMinervaAttributeSet, Mana, OldMana);
}

void UMinervaAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMinervaAttributeSet, MaxMana, OldMaxMana);
}
