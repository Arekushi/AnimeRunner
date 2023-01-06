#pragma once

#include "CoreMinimal.h"
#include "AnimeRunner/Structures/MatchResponse.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "RequestHTTP.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHttpRequestCompleted, const TArray<FMatchResponse>&, Tops, bool, bSuccess);

class FHttpModule;

UCLASS()
class ANIMERUNNER_API URequestHTTP : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	URequestHTTP();
	
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "HTTP", WorldContext = "WorldContextObject"))
		static URequestHTTP* AsyncRequestHTTP(UObject* WorldContextObject, FString URL);

	UPROPERTY(BlueprintAssignable)
		FOnHttpRequestCompleted Completed;

private:
	FHttpModule* HTTP;
	FString URL;
};
