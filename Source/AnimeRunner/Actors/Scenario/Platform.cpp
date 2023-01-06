#include "Platform.h"

#include "Components/BoxComponent.h"
#include "CustomDestructibleActor.h"
#include "DestructibleFloor.h"

#define PRINT_STRING(String) \
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, String);


APlatform::APlatform()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APlatform::BeginPlay()
{
	Super::BeginPlay();

	if (Trigger != nullptr)
	{
		Trigger->bHiddenInGame = true;
	}
}

void APlatform::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatform::DestroyObstaclesAbove(
	ACustomDestructibleActor* Floor,
	const FVector HitLocation)
{
	Cast<ADestructibleFloor>(Floor)->DestroyAllObstaclesAbove(HitLocation);
}

void APlatform::AddObstaclesAbove(
	UChildActorComponent* FloorChildActorComponent,
	const TArray<UChildActorComponent*> ObstaclesAbove)
{
	ADestructibleFloor* Floor = Cast<ADestructibleFloor>(FloorChildActorComponent->GetChildActor());

	if (Floor)
	{
		Floor->ObstaclesAbove = ObstaclesAbove;
		Floor->FOnDamagedDelegate.AddDynamic(this, &APlatform::DestroyObstaclesAbove);
	}
}
