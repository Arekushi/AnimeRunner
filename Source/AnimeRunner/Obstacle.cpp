#include "Obstacle.h"


AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
}

void AObstacle::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}
