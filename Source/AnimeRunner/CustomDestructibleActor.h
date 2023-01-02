// ReSharper disable CppDeprecatedEntity
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleMesh.h"
#include "CustomDestructibleActor.generated.h"

class UTimer;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamaged, ACustomDestructibleActor*, Actor, FVector, HitLocation);


class UDestructibleComponent;

UCLASS()
class ANIMERUNNER_API ACustomDestructibleActor : public AActor
{
	GENERATED_BODY()
	
public:
	ACustomDestructibleActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
		UDestructibleComponent *DestructibleComponent;

	UPROPERTY()
		UTimer* Timer;

	virtual void SetupDestructibleComponent();

public:
	UFUNCTION()
		void OnOverlapBegin(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnDamaged(
			ACustomDestructibleActor* Actor,
			FVector HitLocation);
	
	UPROPERTY(EditAnywhere)
		UDestructibleMesh* DestructibleMesh;

	UPROPERTY(EditAnywhere)
		float Damage;

	UPROPERTY(EditAnywhere)
		float DamageRadius;

	UPROPERTY(EditAnywhere)
		float ImpulseStrength;

	UPROPERTY(EditAnywhere)
		bool CanDamaged;

	UPROPERTY(BlueprintAssignable)
		FOnDamaged FOnDamagedDelegate;

	UFUNCTION(BlueprintCallable)
		virtual void Destruct(const FVector HitLocation);

	UFUNCTION(BlueprintCallable)
		virtual void DisableCollision();

protected:
	virtual void ApplyDamage(FVector HitLocation);
	
};
