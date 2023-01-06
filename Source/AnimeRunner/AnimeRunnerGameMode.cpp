#include "AnimeRunnerGameMode.h"

#include "AnimeRunnerGameInstance.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpRequest.h"
#include "Structures/MatchRequest.h"

#define PRINT(String) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, String);

void AAnimeRunnerGameMode::BeginPlay()
{
	Super::BeginPlay();
	PingAPI();
}

void AAnimeRunnerGameMode::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AAnimeRunnerGameMode::PingAPI()
{
	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->SetURL("https://anime-runners-api.herokuapp.com/api/ping");
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

void AAnimeRunnerGameMode::PostMatchTime()
{
	FString RequestBody;
	FMatchRequest Obj;
	Obj.username = Cast<UAnimeRunnerGameInstance>(GetGameInstance())->Username;
	Obj.time_reached = Time;
	FJsonObjectConverter::UStructToJsonObjectString(Obj, RequestBody);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL("https://anime-runners-api.herokuapp.com/api/match/register-match");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("api-key"), TEXT("A8cDD9zIzhBS0tpcYyGwoa6ARXJuQU6N"));
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}
