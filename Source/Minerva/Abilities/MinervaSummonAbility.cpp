// Midnight Madness Inc.


#include "MinervaSummonAbility.h"

UMinervaSummonAbility::UMinervaSummonAbility() :
	SpawnSpread(90.f),
	NumMinions(5),
	SpawnDistance(75.f, 300.f)
{
}

TArray<FVector> UMinervaSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector(), Location = GetAvatarActorFromActorInfo()->GetActorLocation(),
		LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);
	const float DeltaSpread = SpawnSpread / NumMinions;
	TArray<FVector> SpawnLocations;

	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(SpawnDistance.X, SpawnDistance.Y);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, ChosenSpawnLocation + FVector(0.f, 0.f, 400.f), ChosenSpawnLocation - FVector(0.f, 0.f, 400.f), ECC_Visibility);
		if (Hit.bBlockingHit) ChosenSpawnLocation = Hit.ImpactPoint;
		SpawnLocations.Add(ChosenSpawnLocation);
	}
	
	return SpawnLocations;
}

TSubclassOf<APawn> UMinervaSummonAbility::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	return MinionClasses[Selection];
}
