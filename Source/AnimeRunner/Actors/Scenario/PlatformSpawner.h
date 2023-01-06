#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

class APlatform;

UCLASS()
class ANIMERUNNER_API APlatformSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	APlatformSpawner();
	FActorSpawnParameters SpawnInfo = FActorSpawnParameters();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<APlatform>> Platforms;
	
	TArray<APlatform*> PreviousPlatforms;
	int PreviousPlatformIndex;

public:
	UFUNCTION()
		virtual APlatform* SpawnNextPlatform();

	UFUNCTION()
		void OnOverlapBegin(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

protected:
	virtual FVector GetNextSpawnLocation();
	virtual int GenerateNewIndex();
	
};
