#pragma once

#include "CoreMinimal.h"
#include "CustomDestructibleActor.h"
#include "DestructibleFloor.generated.h"

UCLASS()
class ANIMERUNNER_API ADestructibleFloor : public ACustomDestructibleActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UChildActorComponent*> ObstaclesAbove;
	
	FORCEINLINE
		TArray<UChildActorComponent*> GetActorsAbove() { return ObstaclesAbove; }

	UFUNCTION()
		void DestroyAllObstaclesAbove(FVector HitLocation);
	
};
