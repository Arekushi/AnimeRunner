#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

class UTimer;

UCLASS()
class ANIMERUNNER_API AWall : public AActor
{
	GENERATED_BODY()
	
public:
	AWall();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void MoveWall(const float DeltaTime);
	FTimerHandle AddTimer;
	bool Active;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Multiplier;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    	float Adder;
	
	UPROPERTY()
		UTimer* Timer;

	UFUNCTION()
		virtual void StartMultiplier();

};
