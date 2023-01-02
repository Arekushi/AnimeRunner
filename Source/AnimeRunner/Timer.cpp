#include "Timer.h"


UTimer::UTimer()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTimer::BeginPlay()
{
	Super::BeginPlay();
}

void UTimer::TickComponent(
	const float DeltaTime,
	const ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTimer::SetTimer(
	const FTimerDelegate Delegate,
	const float DelaySeconds,
	const float FirstDelaySeconds)
{
	if (!World)
	{
		World = GEngine->GetWorldFromContextObjectChecked(this);
		// World = GetWorld();
	}
	
	FTimerHandle TimerHandle;
	FTimerManager& TimerManager = World->GetTimerManager();
	TimerManager.SetTimer(TimerHandle, Delegate, DelaySeconds, false, FirstDelaySeconds);
}

void UTimer::SetTimerLoop(
	FTimerHandle& Timer,
	const FTimerDelegate Delegate,
	const float DelaySeconds,
	const float FirstDelaySeconds)
{
	if (!World)
	{
		World = GEngine->GetWorldFromContextObjectChecked(this);
		// World = GetWorld();
	}
	
	FTimerManager& TimerManager = World->GetTimerManager();
	TimerManager.SetTimer(Timer, Delegate, DelaySeconds, true, FirstDelaySeconds);
}

void UTimer::Clear(FTimerHandle Timer)
{
	FTimerManager& TimerManager = World->GetTimerManager();
	TimerManager.ClearTimer(Timer);
}
