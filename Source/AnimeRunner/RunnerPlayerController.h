#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RunnerPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class ANIMERUNNER_API ARunnerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
		FOnDeath OnDeathDelegate;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void OnDeath();
	
};
