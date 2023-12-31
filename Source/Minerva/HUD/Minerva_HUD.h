// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Minerva_HUD.generated.h"

class UAbilitySystemComponent;
class UAttributeMenuWidgetController;
class UAttributeSet;
class UMinervaUserWidget;
class UOverlayWidgetController;

struct FWidgetControllerParams;

UCLASS()
class MINERVA_API AMinerva_HUD : public AHUD
{
	GENERATED_BODY()

public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY()
	TObjectPtr<UMinervaUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Minerva_HUD, meta = (AllowPrivateAccess = true))
	TSubclassOf<UMinervaUserWidget> OverlayWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = Minerva_HUD, meta = (AllowPrivateAccess = true))
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Minerva_HUD, meta = (AllowPrivateAccess = true))
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY(BlueprintReadOnly, Category = Minerva_HUD, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Minerva_HUD, meta = (AllowPrivateAccess = true))
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
