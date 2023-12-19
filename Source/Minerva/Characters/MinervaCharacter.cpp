// Midnight Madness Inc.


#include "MinervaCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Minerva/Player/MinervaPlayerState.h"

AMinervaCharacter::AMinervaCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AMinervaCharacter::PossessedBy(AController* NewController)
{
	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void AMinervaCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void AMinervaCharacter::InitAbilityActorInfo()
{
	auto MinervaPlayerState = GetPlayerState<AMinervaPlayerState>();
	check(MinervaPlayerState);
	MinervaPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MinervaPlayerState, this);
	AbilitySystemComponent = MinervaPlayerState->GetAbilitySystemComponent();
	AttributeSet = MinervaPlayerState->GetAttributeSet();
}
