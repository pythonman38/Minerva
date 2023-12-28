// Midnight Madness Inc.


#include "MinervaAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Minerva/HUD/Minerva_HUD.h"
#include "Minerva/HUD/MinervaWidgetController.h"
#include "Minerva/Player/MinervaPlayerState.h"

UOverlayWidgetController* UMinervaAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (auto PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (auto Minvera_HUD = Cast<AMinerva_HUD>(PC->GetHUD()))
		{
			auto PS = PC->GetPlayerState<AMinervaPlayerState>();
			auto ASC = PS->GetAbilitySystemComponent();
			auto AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return Minvera_HUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UMinervaAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (auto PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (auto Minvera_HUD = Cast<AMinerva_HUD>(PC->GetHUD()))
		{
			auto PS = PC->GetPlayerState<AMinervaPlayerState>();
			auto ASC = PS->GetAbilitySystemComponent();
			auto AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return Minvera_HUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}
