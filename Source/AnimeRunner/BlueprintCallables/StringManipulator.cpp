#include "AnimeRunner/BlueprintCallables/StringManipulator.h"

#define PRINT(String) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, String);

FString UStringManipulator::Clamp(FString Text, const int MaxLength)
{
	if (Text.Len() > MaxLength)
	{
		Text = Text.LeftChop(1);
	}
	
	return Text;
}
