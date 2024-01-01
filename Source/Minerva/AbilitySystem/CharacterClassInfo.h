// Midnight Madness Inc.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Elementalist,
	Warrior,
	Ranger
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ClassDefaults)
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
};

UCLASS()
class MINERVA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CharacterClassDefaults)
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CommonClassDefaults)
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CommonClassDefaults)
	TSubclassOf<UGameplayEffect> VitalAttributes;
};
