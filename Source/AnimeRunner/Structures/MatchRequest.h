// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#pragma once

#include "CoreMinimal.h"
#include "MatchRequest.generated.h"

USTRUCT(BlueprintType)
struct FMatchRequest
{
	GENERATED_BODY()
	
	UPROPERTY()
		FString username;

	UPROPERTY()
		float time_reached;
};
