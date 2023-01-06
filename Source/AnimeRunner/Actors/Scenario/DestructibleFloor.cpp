#include "DestructibleFloor.h"

#define PRINT_STRING(String) \
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, String);


void ADestructibleFloor::DestroyAllObstaclesAbove(const FVector HitLocation)
{
	for (const UChildActorComponent* ChildActor : ObstaclesAbove)
	{
		ACustomDestructibleActor* Obstacle = Cast<ACustomDestructibleActor>(ChildActor->GetChildActor());
		
		if (Obstacle)
		{
		    Obstacle->Destruct(HitLocation);
		}
	}
}
