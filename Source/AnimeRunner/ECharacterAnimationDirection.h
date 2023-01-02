#pragma once

#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum ECharacterAnimationDirection
{
	Up UMETA(DisplayName = "Up"),
	Down UMETA(DisplayName = "Down"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right")
};
