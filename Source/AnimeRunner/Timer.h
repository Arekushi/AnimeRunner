#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Timer.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ANIMERUNNER_API UTimer : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTimer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;
	
	void SetTimer(
		const FTimerDelegate Delegate,
		const float DelaySeconds,
		const float FirstDelaySeconds = -1);

	void SetTimerLoop(
		FTimerHandle& Timer,
		const FTimerDelegate Delegate,
		const float DelaySeconds,
		const float FirstDelaySeconds = -1);

	void Clear(FTimerHandle Timer);

protected:
	UPROPERTY(VisibleAnywhere, category = "Timer")
		UWorld* World;
	
};
