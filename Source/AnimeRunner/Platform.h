#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Platform.generated.h"

class ADestructibleFloor;
class AObstacle;
class UBoxComponent;
class ACustomDestructibleActor;

UCLASS()
class ANIMERUNNER_API APlatform : public AActor
{
	GENERATED_BODY()
	
public:
	APlatform();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Triggers")
		UBoxComponent* Trigger;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Triggers")
		UBoxComponent* SpawnLocation;

	UFUNCTION()
		void DestroyObstaclesAbove(ACustomDestructibleActor* Floor, FVector HitLocation);

public:
	UFUNCTION(BlueprintCallable)
		void AddObstaclesAbove(
			UChildActorComponent* FloorChildActorComponent,
			TArray<UChildActorComponent*> ObstaclesAbove);
	
	FORCEINLINE
		UBoxComponent* GetTrigger() const { return Trigger; }

	FORCEINLINE
		UBoxComponent* GetSpawnLocation() const { return SpawnLocation; }
	
};
