#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AnimeRunnerGameInstance.generated.h"


UCLASS()
class ANIMERUNNER_API UAnimeRunnerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UAnimeRunnerGameInstance();
	
	UPROPERTY(BlueprintReadWrite)
		FString Username;
	
};
