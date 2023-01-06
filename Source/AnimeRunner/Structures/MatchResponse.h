// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#pragma once

#include "CoreMinimal.h"
#include "MatchResponse.generated.h"

USTRUCT(BlueprintType)
struct FMatchResponse
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FDateTime created_at;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString username;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float time_reached;
};
