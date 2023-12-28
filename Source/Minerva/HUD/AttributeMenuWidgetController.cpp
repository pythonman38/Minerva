// Midnight Madness Inc.


#include "AttributeMenuWidgetController.h"

#include "Minerva/AbilitySystem/AttributeInfo.h"
#include "Minerva/AbilitySystem/MinervaAttributeSet.h"
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
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	auto AS = CastChecked<UMinervaAttributeSet>(AttributeSet);

	check(AttributeInfo);
	
	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	auto Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}


