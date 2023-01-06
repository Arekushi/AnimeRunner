#include "AnimeRunner/BlueprintCallables/TimerUtils.h"

FString UTimerUtils::FloatTimerToString(const float Time)
{
	const int Minutes = UE4::SSE::TruncToInt(Time / 60);
	const int Seconds = UE4::SSE::TruncToInt(fmod(Time, 60));
	const int Milliseconds = UE4::SSE::TruncToInt(fmod(Time * 1000, 1000));
	
	return FString::Printf(TEXT("%02d:%02d:%03d"), Minutes, Seconds, Milliseconds);
}
