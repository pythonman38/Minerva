// Midnight Madness Inc.


#include "MinervaEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/SphereComponent.h"
#include "Minerva/AbilitySystem/MinervaAttributeSet.h"

AMinervaEffectActor::AMinervaEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AMinervaEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMinervaEffectActor::OnSphereBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AMinervaEffectActor::OnSphereEndOverlap);
}

void AMinervaEffectActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack!
	if (auto ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const auto MinervaAttributeSet = Cast<UMinervaAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UMinervaAttributeSet::StaticClass()));
		auto MutableMinervaAttributeSet = const_cast<UMinervaAttributeSet*>(MinervaAttributeSet);
		MutableMinervaAttributeSet->SetHealth(MinervaAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AMinervaEffectActor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


