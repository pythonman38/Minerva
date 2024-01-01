// Midnight Madness Inc.


#include "MinervaAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Minerva/Game/MinervaGameModeBase.h"
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

void UMinervaAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	if (auto MinervaGameMode = Cast<AMinervaGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		auto AvatarActor = ASC->GetAvatarActor();
		auto CharacterClassInfo = MinervaGameMode->CharacterClassInfo;
		const auto ClassDefaultInfo = MinervaGameMode->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

		auto PrimaryAttributesContextHandle = ASC->MakeEffectContext();
		PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
		const auto PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

		auto SecondaryAttributesContextHandle = ASC->MakeEffectContext();
		SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
		const auto SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

		auto VitalAttributesContextHandle = ASC->MakeEffectContext();
		VitalAttributesContextHandle.AddSourceObject(AvatarActor);
		const auto VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
	}
	else return;
}
