// Midnight Madness Inc.


#include "MinervaCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Minerva/AbilitySystem/MinervaAbilitySystemComponent.h"
#include "Minerva/Minerva.h"

AMinervaCharacterBase::AMinervaCharacterBase() :
	bDead(false),
	MinionCount(0)
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

UAnimMontage* AMinervaCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AMinervaCharacterBase::MulticastHandleDeath_Implementation()
{
	if (Weapon)
	{
		Weapon->SetSimulatePhysics(true);
		Weapon->SetEnableGravity(true);
		Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	}

	if (DeathSound) UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();

	bDead = true;
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
	ApplyEffectToSelf(DefaultResistanceAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AMinervaCharacterBase::AddCharacterAbilities()
{
	auto MinervaASC = CastChecked<UMinervaAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;
	MinervaASC->AddCharacterAbilities(StartupAbilities);
}

FVector AMinervaCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const auto& GameplayTags = FMinervaGameplayTags::Get();
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Weapon) && IsValid(Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Tail))
	{
		return GetMesh()->GetSocketLocation(TailSocketName);
	}

	return FVector();
}

bool AMinervaCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* AMinervaCharacterBase::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> AMinervaCharacterBase::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

UNiagaraSystem* AMinervaCharacterBase::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

FTaggedMontage AMinervaCharacterBase::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (FTaggedMontage TaggedMontage : AttackMontages)
	{
		if (TaggedMontage.MontageTag == MontageTag) return TaggedMontage;
	}

	return FTaggedMontage();
}

int32 AMinervaCharacterBase::GetMinionCount_Implementation()
{
	return MinionCount;
}

void AMinervaCharacterBase::IncrementMinionCount_Implementation(int32 Amount)
{
	MinionCount += Amount;
}

void AMinervaCharacterBase::DecrementMinionCount_Implementation(int32 Amount)
{
	MinionCount -= Amount;
}

void AMinervaCharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		auto DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		StartDissolveTimeline(DynamicMatInst);
	}
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		auto DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		if (Weapon) Weapon->SetMaterial(0, DynamicMatInst);
		StartWeaponDissolveTimeline(DynamicMatInst);
	}
}

UAbilitySystemComponent* AMinervaCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMinervaCharacterBase::Die()
{
	if (Weapon) Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}
