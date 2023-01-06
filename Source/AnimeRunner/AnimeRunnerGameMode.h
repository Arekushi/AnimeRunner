#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AnimeRunnerGameMode.generated.h"


UCLASS()
class ANIMERUNNER_API AAnimeRunnerGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float Time;

protected:
	virtual void PingAPI();

	UFUNCTION(BlueprintCallable)
		virtual void PostMatchTime();
	
};
