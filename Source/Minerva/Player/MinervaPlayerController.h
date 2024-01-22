// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "MinervaPlayerController.generated.h"

class IEnemyInterface;
class UDamageTextComponent;
class UInputAction;
class UInputMappingContext;
class UMinervaAbilitySystemComponent;
class UMinervaInputConfig;
class USplineComponent;

struct FInputActionValue;

UCLASS()
class MINERVA_API AMinervaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMinervaPlayerController();

	void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter);

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void AddInputMappingContext();

	void Move(const FInputActionValue& Value);

	void SetInputModes();

	void CursorTrace();

	void AbilityInputTagPressed(FGameplayTag InputTag);

	void AbilityInputTagReleased(FGameplayTag InputTag);

	void AbilityInputTagHeld(FGameplayTag InputTag);

	void AutoRun();

	void ShiftPressed() { bShiftKeyDown = true; }
	void ShiftReleased() { bShiftKeyDown = false; }

	UMinervaAbilitySystemComponent* GetASC();

private:
	float FollowTime, ShortPressThreshold;

	bool bAutoRunning, bTargeting, bShiftKeyDown;

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;

	FVector CachedDestination;

	FHitResult CursorHit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
	float AutoRunAcceptanceRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> MinervaMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> ShiftAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMinervaInputConfig> InputConfig;

	UPROPERTY(BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMinervaAbilitySystemComponent> MinervaAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = true))
	TObjectPtr<USplineComponent> Spline;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = true))
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
