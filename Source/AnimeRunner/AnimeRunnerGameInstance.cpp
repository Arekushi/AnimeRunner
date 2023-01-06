#include "AnimeRunnerGameInstance.h"

#define PRINT(String) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, String);

UAnimeRunnerGameInstance::UAnimeRunnerGameInstance()
{
	Username = FWindowsPlatformProcess::UserName();
}
