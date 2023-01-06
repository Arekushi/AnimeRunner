#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "AnimeRunner/Enums/CharacterAnimationDirection.h"
#include "AnimeRunner/Enums/CharacterMovementStatus.h"
#include "Persona.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimationDirectionUpdate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMovementStatusUpdate);

class UTimer;

UCLASS()
class ANIMERUNNER_API APersona : public APaperCharacter
{
	GENERATED_BODY()

public:
	APersona();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		bool CanMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Character")
		TEnumAsByte<ECharacterMovementStatus> MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Character")
		TEnumAsByte<ECharacterAnimationDirection> AnimationDirection;

	UPROPERTY()
		UTimer* Timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int HP;

	UFUNCTION(BlueprintCallable)
		void UpdateMovementStatus(const FVector Velocity);

	UFUNCTION(BlueprintCallable)
		void UpdateAnimationDirection(const FVector Velocity);

	UFUNCTION()
		void Animate(float DeltaTime, FVector OldLocation, FVector OldVelocity);

	UFUNCTION(BlueprintCallable)
		void Flip();

	UFUNCTION()
		virtual void ChangeToIdleState();

	UPROPERTY(BlueprintAssignable)
		FOnAnimationDirectionUpdate OnAnimationDirectionUpdateDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnMovementStatusUpdate OnMovementStatusUpdateDelegate;

protected:
	virtual void MoveAxisX(float Value);
	virtual void MoveAxisY(float Value);
	virtual void SetAnimationDirection(TEnumAsByte<ECharacterAnimationDirection> Direction);
	virtual void SetMovementStatus(TEnumAsByte<ECharacterMovementStatus> Status);

private:
	bool IsMoving;
	FTimerDelegate ChangeToIdleStateDelegate;
	
};
