#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"

UINTERFACE(MinimalAPI)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

class ANIMERUNNER_API IDamageable
{
	GENERATED_BODY()

public:
	UFUNCTION(Category="Interact")
	virtual void TakeDamage(int Damage) = 0;
};
