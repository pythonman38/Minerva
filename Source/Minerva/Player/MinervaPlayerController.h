// Midnight Madness Inc 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MinervaPlayerController.generated.h"

class IEnemyInterface;
class UInputAction;
class UInputMappingContext;

struct FInputActionValue;

UCLASS()
class MINERVA_API AMinervaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMinervaPlayerController();

	void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void AddInputMappingContext();

	void Move(const FInputActionValue& Value);

	void SetInputModes();

	void CursorTrace();

private:
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MinervaMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;
};
