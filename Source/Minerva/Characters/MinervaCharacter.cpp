// Midnight Madness Inc.


#include "MinervaCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Minerva/AbilitySystem/MinervaAbilitySystemComponent.h"
#include "Minerva/HUD/Minerva_HUD.h"
#include "Minerva/Player/MinervaPlayerController.h"
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
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AMinervaCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

int32 AMinervaCharacter::GetPlayerLevel()
{
	const auto MinervaPlayerState = GetPlayerState<AMinervaPlayerState>();
	check(MinervaPlayerState);
	return MinervaPlayerState->GetPlayerLevel();
}

void AMinervaCharacter::InitAbilityActorInfo()
{
	auto MinervaPlayerState = GetPlayerState<AMinervaPlayerState>();
	check(MinervaPlayerState);
	MinervaPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MinervaPlayerState, this);
	Cast<UMinervaAbilitySystemComponent>(MinervaPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = MinervaPlayerState->GetAbilitySystemComponent();
	AttributeSet = MinervaPlayerState->GetAttributeSet();
	
	if (auto MinervaPlayerController = Cast<AMinervaPlayerController>(GetController()))
	{
		if (auto Minvera_HUD = Cast<AMinerva_HUD>(MinervaPlayerController->GetHUD())) Minvera_HUD->InitOverlay(MinervaPlayerController, MinervaPlayerState, AbilitySystemComponent, AttributeSet);
	}

	InitializeDefaultAttributes();
}
