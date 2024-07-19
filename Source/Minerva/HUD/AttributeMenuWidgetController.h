// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "MinervaWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;

struct FGameplayAttribute;
struct FGameplayTag;
struct FMinervaAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FMinervaAttributeInfo&, Info);

UCLASS(BlueprintType, Blueprintable)
class MINERVA_API UAttributeMenuWidgetController : public UMinervaWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BindCallbacksToDependencies() override;

	virtual void BroadcastInitialValues() override;

	UFUNCTION(BlueprintCallable)
	void UpgradeAttribute(const FGameplayTag& AttributeTag);

protected:
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnPlayerStatChangedSignature AttributePointsChangedDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Info")
	TObjectPtr<UAttributeInfo> AttributeInfo;
};
