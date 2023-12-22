// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "MinervaEffectActor.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnBeginOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class MINERVA_API AMinervaEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMinervaEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);


private:
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects", meta = (AllowPrivateAccess = "true"))
	float ActorLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects", meta = (AllowPrivateAccess = "true"))
	bool bDestroyOnEffectRemoval;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects", meta = (AllowPrivateAccess = "true"))
	EEffectApplicationPolicy InstantEffectApplicationPolicy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects", meta = (AllowPrivateAccess = "true"))
	EEffectApplicationPolicy DurationEffectApplicationPolicy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects", meta = (AllowPrivateAccess = "true"))
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects", meta = (AllowPrivateAccess = "true"))
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy;

	
};
