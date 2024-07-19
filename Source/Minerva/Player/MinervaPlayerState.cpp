// Midnight Madness Inc.


#include "MinervaPlayerState.h"

#include "Minerva/AbilitySystem/MinervaAbilitySystemComponent.h"
#include "Minerva/AbilitySystem/MinervaAttributeSet.h"
#include "Net/UnrealNetwork.h"

AMinervaPlayerState::AMinervaPlayerState() :
	Level(1),
	XP(1),
	AttributePoints(0),
	SpellPoints(1)
{
	AbilitySystemComponent = CreateDefaultSubobject<UMinervaAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMinervaAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void AMinervaPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMinervaPlayerState, Level);
	DOREPLIFETIME(AMinervaPlayerState, XP);
	DOREPLIFETIME(AMinervaPlayerState, AttributePoints);
	DOREPLIFETIME(AMinervaPlayerState, SpellPoints);
}

void AMinervaPlayerState::AddToXP(int32 InXP)
{
	XP += InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AMinervaPlayerState::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AMinervaPlayerState::AddToAtributePoints(int32 InPoints)
{
	AttributePoints += InPoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AMinervaPlayerState::AddToSpellPoints(int32 InPoints)
{
	SpellPoints += InPoints;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AMinervaPlayerState::SetXP(int32 InXP)
{
	XP = InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AMinervaPlayerState::SetLevel(int32 InLevel)
{
	Level = InLevel;
	OnXPChangedDelegate.Broadcast(Level);
}

void AMinervaPlayerState::OnRep_Level(int32 OldLevel)
{
	OnXPChangedDelegate.Broadcast(Level);
}

void AMinervaPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}

void AMinervaPlayerState::OnRep_AttributePoints(int32 OldAttributePoints)
{
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AMinervaPlayerState::OnRep_SpellPoints(int32 OldSpellPoints)
{
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

UAbilitySystemComponent* AMinervaPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
