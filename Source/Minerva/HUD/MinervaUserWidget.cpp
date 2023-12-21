// Midnight Madness Inc.


#include "MinervaUserWidget.h"

void UMinervaUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
