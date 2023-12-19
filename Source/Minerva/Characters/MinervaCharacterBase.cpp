// Midnight Madness Inc.


#include "MinervaCharacterBase.h"

AMinervaCharacterBase::AMinervaCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMinervaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* AMinervaCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
