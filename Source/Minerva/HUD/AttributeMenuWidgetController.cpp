// Midnight Madness Inc.


#include "AttributeMenuWidgetController.h"

#include "Minerva/AbilitySystem/AttributeInfo.h"
#include "Minerva/AbilitySystem/MinervaAbilitySystemComponent.h"
#include "Minerva/AbilitySystem/MinervaAttributeSet.h"
#include "Minerva/Player/MinervaPlayerState.h"
#include "Minerva/Singletons/MinervaGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	auto AS = CastChecked<UMinervaAttributeSet>(AttributeSet);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda([this, Pair](const FOnAttributeChangeData& Data) 
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			});
	}

	auto MinervaPlayerState = CastChecked<AMinervaPlayerState>(PlayerState);
	MinervaPlayerState->OnAttributePointsChangedDelegate.AddLambda([this](int32 Points)
		{
			AttributePointsChangedDelegate.Broadcast(Points);
		}
	);
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	auto AS = CastChecked<UMinervaAttributeSet>(AttributeSet);

	check(AttributeInfo);
	
	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}

	auto MinervaPlayerState = CastChecked<AMinervaPlayerState>(PlayerState);
	AttributePointsChangedDelegate.Broadcast(MinervaPlayerState->GetAttributePoints());

}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	auto MinervaASC = CastChecked<UMinervaAbilitySystemComponent>(AbilitySystemComponent);
	MinervaASC->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	auto Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}


