// Midnight Madness Inc.


#include "TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	if (const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled()) SendMouseCursorData();
	else
	{
		const auto SpecHandle = GetAbilitySpecHandle();
		const auto OriginalPredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, OriginalPredictionKey).AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);

		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, OriginalPredictionKey);
		if (!bCalledDelegate) SetWaitingOnRemotePlayerData();
	}
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	auto PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);
	const auto OriginalPredictionKey = GetActivationPredictionKey();
	const auto CurrentPredictionKey = AbilitySystemComponent->ScopedPredictionKey;
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), OriginalPredictionKey, DataHandle, FGameplayTag(), CurrentPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates()) ValidData.Broadcast(DataHandle);
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	if (ShouldBroadcastAbilityTaskDelegates()) ValidData.Broadcast(DataHandle);
}
