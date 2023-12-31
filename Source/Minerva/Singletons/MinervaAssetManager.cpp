// Midnight Madness Inc.


#include "MinervaAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "Minerva/Singletons/MinervaGameplayTags.h"


UMinervaAssetManager& UMinervaAssetManager::Get()
{
	check(GEngine);
	auto MinervaAssetManager = Cast<UMinervaAssetManager>(GEngine->AssetManager);
	return *MinervaAssetManager;
}

void UMinervaAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FMinervaGameplayTags::InitializeNativeGameplayTags();

	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}