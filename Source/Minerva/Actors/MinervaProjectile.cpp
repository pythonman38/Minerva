// Midnight Madness Inc.


#include "MinervaProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Minerva/AbilitySystem/MinervaAbilitySystemLibrary.h"
#include "Minerva/Minerva.h"
#include "NiagaraFunctionLibrary.h"

AMinervaProjectile::AMinervaProjectile() :
	bHit(false),
	LifeSpan(10.f)
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AMinervaProjectile::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		if (ImpactSound) UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		if (ImpactEffect) UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		if (LoopingSound) LoopingSoundComponent->Stop();
	}

	Super::Destroyed();
}

void AMinervaProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetFireboltProperties();
}

void AMinervaProjectile::SetFireboltProperties()
{
	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMinervaProjectile::OnSphereBeginOverlap);
	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
}

void AMinervaProjectile::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!DamageEffectSpceHandle.Data.IsValid() || DamageEffectSpceHandle.Data.Get()->GetContext().GetEffectCauser() == OtherActor) return;
	if (!UMinervaAbilitySystemLibrary::IsNotFriend(DamageEffectSpceHandle.Data.Get()->GetContext().GetEffectCauser(), OtherActor)) return;
	if (!bHit)
	{
		if (ImpactSound) UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		if (ImpactEffect) UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		if (LoopingSound) LoopingSoundComponent->Stop();
	}
	
	if (HasAuthority())
	{
		if (auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpceHandle.Data.Get());
		}

		Destroy();
	}
	else bHit = true;
}