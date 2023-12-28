// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MinervaAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class MINERVA_API UMinervaAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UMinervaAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
