// Midnight Madness Inc.


#include "MinervaPlayerState.h"

#include "Minerva/AbilitySystem/MinervaAbilitySystemComponent.h"
#include "Minerva/AbilitySystem/MinervaAttributeSet.h"
#include "Net/UnrealNetwork.h"

AMinervaPlayerState::AMinervaPlayerState() :
	Level(1),
	XP(1)
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

UAbilitySystemComponent* AMinervaPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
