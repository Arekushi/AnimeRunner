#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "Persona.h"
#include "RunnerPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
class APlayerController;

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()
	
	UPROPERTY()
		FString username;

	UPROPERTY()
		float time_reached;
};

UCLASS()
class ANIMERUNNER_API ARunnerPlayer : public APersona, public IDamageable
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

	APlayerController *GetPlayerController() const;
	
	void ToggleInput();
	
	virtual void TakeDamage(int Damage) override;

	UFUNCTION()
		void OnDestroyPlayer(AActor* DestroyedActor);

	void PostTimer();

	UPROPERTY(BlueprintReadWrite)
		bool bGoToMenu;
};
