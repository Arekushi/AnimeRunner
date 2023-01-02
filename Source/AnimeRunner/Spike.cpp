#include "Spike.h"


ASpike::ASpike()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpike::BeginPlay()
{
	Super::BeginPlay();
}

void ASpike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
