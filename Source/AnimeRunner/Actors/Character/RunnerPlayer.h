#pragma once

#include "CoreMinimal.h"
#include "Persona.h"
#include "AnimeRunner/Interfaces/Damageable.h"
#include "Kismet/GameplayStatics.h"
#include "RunnerPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
class APlayerController;

UCLASS()
class ANIMERUNNER_API ARunnerPlayer : public APersona, public IDamageable
{
	GENERATED_BODY()

public:
	ARunnerPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	bool InputEnabled;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* SideViewCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* SpringArm;
	
	FORCEINLINE UCameraComponent* GetSideViewCameraComponent() const { return SideViewCamera; }

	FORCEINLINE APlayerController *GetPlayerController() const
	{
		return UGameplayStatics::GetPlayerController(this, 0);
	}
	
	void ToggleInput();
	
	virtual void TakeDamage(int Damage) override;

	UFUNCTION()
		void OnDestroyPlayer(AActor* DestroyedActor);

	UPROPERTY(BlueprintReadWrite)
		bool bGoToMenu;
};
