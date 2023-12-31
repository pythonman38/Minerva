// Midnight Madness Inc.


#include "MinervaPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SplineComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Minerva/AbilitySystem/MinervaAbilitySystemComponent.h"
#include "Minerva/Input/MinervaInputComponent.h"
#include "Minerva/Interaction/EnemyInterface.h"
#include "Minerva/Singletons/MinervaGameplayTags.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"

AMinervaPlayerController::AMinervaPlayerController() :
	CachedDestination(FVector::ZeroVector),
	FollowTime(0.f),
	ShortPressThreshold(0.5f),
	AutoRunAcceptanceRadius(50.f),
	bAutoRunning(false),
	bTargeting(false),
	bShiftKeyDown(false)
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AMinervaPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

	AutoRun();
}

void AMinervaPlayerController::AutoRun()
{
	if (!bAutoRunning) return;

	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius) bAutoRunning = false;
	}
}

void AMinervaPlayerController::BeginPlay()
{
	AddInputMappingContext();

	SetInputModes();
}

void AMinervaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (auto MinervaInputComponent = CastChecked<UMinervaInputComponent>(InputComponent))
	{
		// Moving
		MinervaInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMinervaPlayerController::Move);

		// Shift Spell Casting
		MinervaInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AMinervaPlayerController::ShiftPressed);
		MinervaInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AMinervaPlayerController::ShiftReleased);

		// Spell Casting
		MinervaInputComponent->BindAbilityActions(InputConfig, this, &AMinervaPlayerController::AbilityInputTagPressed, &AMinervaPlayerController::AbilityInputTagReleased, 
			&AMinervaPlayerController::AbilityInputTagHeld);
	}
}

void AMinervaPlayerController::AddInputMappingContext()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (Subsystem) Subsystem->AddMappingContext(MinervaMappingContext, 0);
	}
}

void AMinervaPlayerController::Move(const FInputActionValue& Value)
{
	// Input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// Find out which way is forward
	const FRotator Rotation = GetControlRotation(), YawRotation(0, Rotation.Yaw, 0);

	// Get directional vectors
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Add movement
	if (auto ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMinervaPlayerController::SetInputModes()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AMinervaPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
}

void AMinervaPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FMinervaGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AMinervaPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FMinervaGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}
	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
	if (!bTargeting && !bShiftKeyDown)
	{
		const APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if (auto NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
				}
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AMinervaPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{

	if (!InputTag.MatchesTagExact(FMinervaGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}

	if (bTargeting || bShiftKeyDown)
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		if (CursorHit.bBlockingHit) CachedDestination = CursorHit.ImpactPoint;

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UMinervaAbilitySystemComponent* AMinervaPlayerController::GetASC()
{
	if (MinervaAbilitySystemComponent == nullptr)
	{
		MinervaAbilitySystemComponent = Cast<UMinervaAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	
	return MinervaAbilitySystemComponent;
}
