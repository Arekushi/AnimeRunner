#include "PlatformSpawner.h"

#include "Platform.h"
#include "Components/BoxComponent.h"

#define PRINT(String) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, String);

APlatformSpawner::APlatformSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	PreviousPlatformIndex = -1;
}

void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 3; i++)
	{
		SpawnNextPlatform();
	}
}

void APlatformSpawner::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

APlatform* APlatformSpawner::SpawnNextPlatform()
{
	const FVector SpawnLocation = GetNextSpawnLocation();
	const FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	
	APlatform* NextPlatform = GetWorld()->SpawnActor<APlatform>(
		Platforms[GenerateNewIndex()],
		SpawnLocation,
		SpawnRotation,
		SpawnInfo
	);

	if (NextPlatform)
	{
		UBoxComponent* Trigger = NextPlatform->GetTrigger();
		
		if (Trigger)
		{
			Trigger->OnComponentBeginOverlap.AddDynamic(this, &APlatformSpawner::OnOverlapBegin);
		}
		
		PreviousPlatforms.Add(NextPlatform);

		if (PreviousPlatforms.Num() > 7)
		{
			APlatform* FirstPlatform = PreviousPlatforms[0];
			PreviousPlatforms.RemoveAt(0);
			FirstPlatform->Destroy();
		}
	}

	return NextPlatform;
}

void APlatformSpawner::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// Disable Trigger
	OverlappedComponent->UnregisterComponent();
	
	SpawnNextPlatform();
}

FVector APlatformSpawner::GetNextSpawnLocation()
{
	const bool HasPreviousPlatforms = PreviousPlatforms.Num() != 0;
	
	if (HasPreviousPlatforms)
	{
		const APlatform* LastPlatform = PreviousPlatforms.Last();
		return LastPlatform->GetSpawnLocation()->GetComponentTransform().GetTranslation();
	}

	return FVector(1000.0f, 0.0f, 0.0f);
}

int APlatformSpawner::GenerateNewIndex()
{
	int RandomPlatformIndex;

	do
	{
		RandomPlatformIndex = FMath::RandRange(0, Platforms.Num() - 1);
	} while (RandomPlatformIndex == PreviousPlatformIndex);

	PreviousPlatformIndex = RandomPlatformIndex;
	return RandomPlatformIndex;
}
