// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MinervaAIController.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class MINERVA_API AMinervaAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMinervaAIController();

private:
	UPROPERTY(meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
