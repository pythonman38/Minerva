// Midnight Madness Inc.


#include "MinervaCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Minerva/AbilitySystem/LevelUpInfo.h"
#include "Minerva/AbilitySystem/MinervaAbilitySystemComponent.h"
#include "Minerva/HUD/Minerva_HUD.h"
#include "Minerva/Player/MinervaPlayerController.h"
#include "Minerva/Player/MinervaPlayerState.h"
#include "NiagaraComponent.h"

AMinervaCharacter::AMinervaCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComp");
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LevelUpNiagaraComp");
	LevelUpNiagaraComponent->SetupAttachment(GetRootComponent());
	LevelUpNiagaraComponent->bAutoActivate = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CharacterClass = ECharacterClass::Elementalist;
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

int32 AMinervaCharacter::GetPlayerLevel_Implementation()
{
	const auto MinervaPlayerState = GetPlayerState<AMinervaPlayerState>();
	check(MinervaPlayerState);
	return MinervaPlayerState->GetPlayerLevel();
}

void AMinervaCharacter::AddToXP_Implementation(int32 InXP)
{
	auto MinervaPlayerState = GetPlayerState<AMinervaPlayerState>();
	check(MinervaPlayerState);
	MinervaPlayerState->AddToXP(InXP);
}

void AMinervaCharacter::AddToPlayerLevel_Implementation(int32 AmountToAdd)
{
	auto MinervaPlayerState = GetPlayerState<AMinervaPlayerState>();
	check(MinervaPlayerState);
	MinervaPlayerState->AddToLevel(AmountToAdd);
}

void AMinervaCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	auto MinervaPlayerState = GetPlayerState<AMinervaPlayerState>();
	check(MinervaPlayerState);
	MinervaPlayerState->AddToAtributePoints(InAttributePoints);
}

void AMinervaCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	auto MinervaPlayerState = GetPlayerState<AMinervaPlayerState>();
	check(MinervaPlayerState);
	MinervaPlayerState->AddToSpellPoints(InSpellPoints);
}

void AMinervaCharacter::LevelUp_Implementation()
{
	MulticastLevelUpParticles();
}

int32 AMinervaCharacter::GetXP_Implementation()
{
	const auto MinervaPlayerState = GetPlayerState<AMinervaPlayerState>();
	check(MinervaPlayerState);
	return MinervaPlayerState->GetXP();
}

int32 AMinervaCharacter::GetAttributePointsReward_Implementation(int32 Level)
{
	const auto MinervaPlayerState = GetPlayerState<AMinervaPlayerState>();
	check(MinervaPlayerState);
	return MinervaPlayerState->LevelUpInfo->LevelUpInformation[Level].AttributePointAward;
}

int32 AMinervaCharacter::GetSpellPointsReward_Implementation(int32 Level)
{
	const auto MinervaPlayerState = GetPlayerState<AMinervaPlayerState>();
	check(MinervaPlayerState);
	return MinervaPlayerState->LevelUpInfo->LevelUpInformation[Level].SpellPointAward;
}

int32 AMinervaCharacter::FindLevelForXP_Implementation(int32 InXP)
{
	const auto MinervaPlayerState = GetPlayerState<AMinervaPlayerState>();
	check(MinervaPlayerState);
	return MinervaPlayerState->LevelUpInfo->FindLevelForXP(InXP);
}

int32 AMinervaCharacter::GetAttributePoints_Implementation() const
{
	const auto MinervaPlayerState = GetPlayerState<AMinervaPlayerState>();
	check(MinervaPlayerState);
	return MinervaPlayerState->GetAttributePoints();
}

int32 AMinervaCharacter::GetSpellPoints_Implementation() const
{
	const auto MinervaPlayerState = GetPlayerState<AMinervaPlayerState>();
	check(MinervaPlayerState);
	return MinervaPlayerState->GetSpellPoints();
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

void AMinervaCharacter::MulticastLevelUpParticles_Implementation() const
{
	if (IsValid(LevelUpNiagaraComponent))
	{
		const auto CameraLocation = TopDownCameraComponent->GetComponentLocation(), NiagaraSystemLocation = LevelUpNiagaraComponent->GetComponentLocation();
		const auto ToCameraRotation = (CameraLocation - NiagaraSystemLocation).Rotation();
		LevelUpNiagaraComponent->SetWorldRotation(ToCameraRotation);
		LevelUpNiagaraComponent->Activate(true);
	}
}
