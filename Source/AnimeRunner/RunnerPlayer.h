#pragma once

#include "CoreMinimal.h"
#include "Persona.h"
#include "RunnerPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
class APlayerController;

UCLASS()
class ANIMERUNNER_API ARunnerPlayer : public APersona
{
	GENERATED_BODY()

public:
	ARunnerPlayer();

protected:
	virtual void BeginPlay() override;

private:
	bool InputEnabled;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* SideViewCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* SpringArm;
	
	FORCEINLINE
		UCameraComponent* GetSideViewCameraComponent() const { return SideViewCamera; }
	
	UFUNCTION()
		void OnOverlapBegin(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	APlayerController *GetPlayerController() const;
	void ToggleInput();
};
