#include "PlatformSpawner.h"

#include "Platform.h"
#include "Engine.h"
#include "Components/BoxComponent.h"

#define PRINT_STRING(String) \
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, String);

APlatformSpawner::APlatformSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 3; i++)
	{
		SpawnPlatform();
	}
}

void APlatformSpawner::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatformSpawner::SpawnPlatform()
{
	APlatform* NextPlatform = ConstructNextPlatform();

	if (NextPlatform)
	{
		UBoxComponent* Trigger = NextPlatform->GetTrigger();

		if (Trigger)
		{
			Trigger->OnComponentBeginOverlap.AddDynamic(this, &APlatformSpawner::OnOverlapBegin);
		}

		PreviousPlatforms.Add(NextPlatform);

		if (PreviousPlatforms.Num() > 5)
		{
			APlatform* FirstPlatform = PreviousPlatforms[0];
			PreviousPlatforms.RemoveAt(0);
			FirstPlatform->Destroy();
		}
	}
}

void APlatformSpawner::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	OverlappedComponent->UnregisterComponent();
	SpawnPlatform();
}

APlatform* APlatformSpawner::ConstructNextPlatform()
{
	const FVector SpawnLocation = GetSpawnLocation();
	const FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	const int RandomPlatformIndex = FMath::RandRange(0, Platforms.Num() - 1);
	
	APlatform* NextPlatform = GetWorld()->SpawnActor<APlatform>(
		Platforms[RandomPlatformIndex],
		SpawnLocation,
		SpawnRotation,
		SpawnInfo
	);

	return NextPlatform;
}

FVector APlatformSpawner::GetSpawnLocation()
{
	const bool HasPreviousPlatforms = PreviousPlatforms.Num() != 0;
	
	if (HasPreviousPlatforms)
	{
		const APlatform* LastPlatform = PreviousPlatforms.Last();
		return LastPlatform->GetSpawnLocation()->GetComponentTransform().GetTranslation();
	}

	return FVector(1000.0f, 0.0f, 0.0f);
}
