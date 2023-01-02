#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spike.generated.h"

UCLASS()
class ANIMERUNNER_API ASpike : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpike();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
