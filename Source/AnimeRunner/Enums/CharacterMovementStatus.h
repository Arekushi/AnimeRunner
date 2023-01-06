#pragma once

#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum ECharacterMovementStatus
{
	Stop UMETA(DisplayName = "Stop"),
	Walk UMETA(DisplayName = "Walk"),
	Run UMETA(DisplayName = "Run"),
	Jump UMETA(DisplayName = "Jump"),
	Fall UMETA(DisplayName = "Fall"),
	Idle UMETA(DisplayName = "Idle")
};
