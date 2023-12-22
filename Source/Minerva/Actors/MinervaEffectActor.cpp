// Midnight Madness Inc.


#include "MinervaEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

AMinervaEffectActor::AMinervaEffectActor() :
	ActorLevel(1.f),
	InstantEffectApplicationPolicy(EEffectApplicationPolicy::DoNotApply),
	DurationEffectApplicationPolicy(EEffectApplicationPolicy::DoNotApply),
	InfiniteEffectApplicationPolicy(EEffectApplicationPolicy::DoNotApply),
	InfiniteEffectRemovalPolicy(EEffectRemovalPolicy::RemoveOnEndOverlap),
	bDestroyOnEffectRemoval(false)
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AMinervaEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMinervaEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (auto ASCInterface = Cast<IAbilitySystemInterface>(TargetActor))
	{
		auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (TargetASC == nullptr) return;

		check(GameplayEffectClass);
		auto EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const auto EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
		const auto ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		if (const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite)
		{
			if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap) ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
		}
	}
}

void AMinervaEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap) ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap) ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap) ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
}

void AMinervaEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}

		for (auto& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}
