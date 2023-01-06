#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StringManipulator.generated.h"

UCLASS()
class ANIMERUNNER_API UStringManipulator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "String Manipulation")
		static FString Clamp(FString Text, int MaxLength);
};
