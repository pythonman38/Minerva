// Midnight Madness Inc.


#include "MinervaWidgetController.h"

void UMinervaWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UMinervaWidgetController::BroadcastInitialValues()
{
}

void UMinervaWidgetController::BindCallbacksToDependencies()
{
}
