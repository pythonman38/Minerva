// Midnight Madness Inc.


#include "OverlayWidgetController.h"

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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MinervaAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MinervaAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MinervaAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MinervaAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
