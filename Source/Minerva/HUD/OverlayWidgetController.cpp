// Midnight Madness Inc.


#include "OverlayWidgetController.h"

#include "Minerva/AbilitySystem/AbilityInfo.h"
#include "Minerva/AbilitySystem/MinervaAbilitySystemComponent.h"
#include "Minerva/AbilitySystem/MinervaAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const auto MinervaAttributeSet = CastChecked<UMinervaAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(MinervaAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(MinervaAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(MinervaAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(MinervaAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const auto MinervaAttributeSet = CastChecked<UMinervaAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MinervaAttributeSet->GetHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) {OnHealthChanged.Broadcast(Data.NewValue); });
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MinervaAttributeSet->GetMaxHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) {OnMaxHealthChanged.Broadcast(Data.NewValue); });
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MinervaAttributeSet->GetManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) {OnManaChanged.Broadcast(Data.NewValue); });
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MinervaAttributeSet->GetMaxManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) {OnMaxManaChanged.Broadcast(Data.NewValue); });

	if (UMinervaAbilitySystemComponent* MinervaASC = Cast<UMinervaAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (MinervaASC->bStartupAbilitiesGiven) OnInitializeStartupAbilities(MinervaASC);
		else MinervaASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);

		MinervaASC->EffectAssetTags.AddLambda([this](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag : AssetTags)
				{
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					if (Tag.MatchesTag(MessageTag))
					{
						const auto Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		);
	}
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UMinervaAbilitySystemComponent* MinervaAbilitySystemComponent)
{
	// TODO: Get information about all given ablities, look up their Ability Info, and broadcast it to widgets.
	if (!MinervaAbilitySystemComponent->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, MinervaAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
		{
			// TODO: Need a way to figure out the ability tag for a given ability spec!
			FMinervaAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(MinervaAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
			Info.InputTag = MinervaAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
			AbilityInfoDelegate.Broadcast(Info);
		}
	);
	MinervaAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}
