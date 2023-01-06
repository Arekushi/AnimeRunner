#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TimerUtils.generated.h"

UCLASS()
class ANIMERUNNER_API UTimerUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Time Utils")
		static FString FloatTimerToString(float Time);
	
};
