#include "Wall.h"

#include "AnimeRunner/ActorComponents/Timer.h"


AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Timer */
	Timer = CreateDefaultSubobject<UTimer>(TEXT("Timer"));
	
	Multiplier = 300;
	Adder = 2;
	Active = true;
}

void AWall::BeginPlay()
{
	Super::BeginPlay();
	GetRootComponent()->ComponentVelocity = FVector(25, 0, 0);
	OnDestroyed.AddDynamic(this, &AWall::OnWallDestroyed);
	
	StartMultiplier();
}

void AWall::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Active)
	{
		MoveWall(DeltaTime);
	}
}

void AWall::MoveWall(const float DeltaTime)
{
	const FVector CurrentLocation = GetActorLocation();
	SetActorLocation(CurrentLocation + FVector(Multiplier * DeltaTime, 0, 0), true);
}

void AWall::StartMultiplier()
{
	FTimerDelegate AddDelegate;
	
	AddDelegate.BindLambda([&]
	{
		Multiplier += Adder;
		Adder *= 1.05;
	});
	
	Timer->SetTimerLoop(AddTimer, AddDelegate, 1);
}

void AWall::OnWallDestroyed(AActor* DestroyedActor)
{
	Deactivate();
}

void AWall::Deactivate()
{
	Active = false;
	Timer->Clear(AddTimer);
}
