// Midnight Madness Inc.


#include "MinervaCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "Minerva/AbilitySystem/MinervaAbilitySystemComponent.h"
#include "Minerva/Minerva.h"

AMinervaCharacterBase::AMinervaCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMinervaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMinervaCharacterBase::InitAbilityActorInfo()
{
}

void AMinervaCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	auto ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const auto SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AMinervaCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AMinervaCharacterBase::AddCharacterAbilities()
{
	auto MinervaASC = CastChecked<UMinervaAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;
	MinervaASC->AddCharacterAbilities(StartupAbilities);
}

FVector AMinervaCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

UAbilitySystemComponent* AMinervaCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
