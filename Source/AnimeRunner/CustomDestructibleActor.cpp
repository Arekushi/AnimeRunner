// ReSharper disable CppDeprecatedEntity
#include "CustomDestructibleActor.h"

#include "DestructibleComponent.h"
#include "Timer.h"
#include "Wall.h"

#define PRINT_STRING(String) \
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, String);


ACustomDestructibleActor::ACustomDestructibleActor()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Timer */
	Timer = CreateDefaultSubobject<UTimer>(TEXT("Timer"));

	Damage = 500.0f;
	DamageRadius = 10.0f;
	ImpulseStrength = 1.0f;
	CanDamaged = true;
}

void ACustomDestructibleActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetupDestructibleComponent();
	FOnDamagedDelegate.AddDynamic(this, &ACustomDestructibleActor::OnDamaged);
}

void ACustomDestructibleActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACustomDestructibleActor::SetupDestructibleComponent()
{
	DestructibleComponent = FindComponentByClass<UDestructibleComponent>();

	if (DestructibleComponent)
	{
		DestructibleComponent->OnComponentBeginOverlap.Clear();
		DestructibleComponent->OnComponentBeginOverlap.AddDynamic(this, &ACustomDestructibleActor::OnOverlapBegin);
	}
}

void ACustomDestructibleActor::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (CanDamaged)
	{
		const AWall* Wall = Cast<AWall>(OtherActor);

		if (Wall)
		{
			PRINT_STRING("Colisão com Wall e o objeto quebrável!");
			const FVector HitLocation = Wall->GetActorLocation();
			Destruct(HitLocation);
		}
	}
}

void ACustomDestructibleActor::OnDamaged(
	ACustomDestructibleActor* Actor,
	FVector HitLocation)
{
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &ACustomDestructibleActor::DisableCollision);
	Timer->SetTimer(Delegate, 0.2f);
}

void ACustomDestructibleActor::Destruct(const FVector HitLocation)
{
	CanDamaged = false;
	FOnDamagedDelegate.Broadcast(this, HitLocation);
	DestructibleComponent->SetDestructibleMesh(DestructibleMesh);
	
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &ACustomDestructibleActor::ApplyDamage, HitLocation);
	Timer->SetTimer(Delegate, 0.1f);
}

void ACustomDestructibleActor::DisableCollision()
{
	DestructibleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACustomDestructibleActor::ApplyDamage(const FVector HitLocation)
{
	DestructibleComponent->AddImpulseAtLocation(
		FVector(0.0f, 0.0f, -1.0f),
		HitLocation
	);
	DestructibleComponent->ApplyRadiusDamage(
		Damage,
		HitLocation,
		DamageRadius,
		ImpulseStrength,
		false
	);
}
