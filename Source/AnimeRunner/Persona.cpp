#include "Persona.h"

#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ECharacterMovementStatus.h"
#include "ECharacterAnimationDirection.h"
#include "Timer.h"

#define PRINT_STRING(String) \
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, String);


APersona::APersona()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Timer */
	Timer = CreateDefaultSubobject<UTimer>(TEXT("Timer"));

	/* Sprite */
	UPaperFlipbookComponent* Flipbook = GetSprite();
	Flipbook->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	Flipbook->SetUsingAbsoluteRotation(true);
	Flipbook->CastShadow = true;

	/* Capsule */
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->InitCapsuleSize(42.f, 96.f);
	Capsule->BodyInstance.bLockRotation = true;

	/* Movement */
	UCharacterMovementComponent* CharacterMov = GetCharacterMovement();
	CharacterMov->bOrientRotationToMovement = false;
	CharacterMov->GravityScale = 2.0f;
	CharacterMov->AirControl = 0.8f;
	CharacterMov->JumpZVelocity = 1000.0f;
	CharacterMov->GroundFriction = 3.0f;
	CharacterMov->MaxWalkSpeed = 600.0f;
	CharacterMov->MaxFlySpeed = 600.0f;
	CharacterMov->bUseFlatBaseForFloorChecks = true;
}

void APersona::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APersona::BeginPlay()
{
	Super::BeginPlay();
	
	MovementStatus = Stop;
	AnimationDirection = Up;
	CanMove = true;
	OnCharacterMovementUpdated.AddDynamic(this, &APersona::Animate);
	ChangeToIdleStateDelegate.BindUObject(this, &APersona::ChangeToIdleState);
}

void APersona::UpdateMovementStatus(const FVector Velocity)
{
	const float VectorLenght = Velocity.Size();
	const FVector VelocityNormalized = Velocity.GetSafeNormal();
	const float Z = VelocityNormalized.Z;
    const bool IsFalling = GetCharacterMovement()->IsFalling();
	const bool IsFallingDown = Z <= 0;
	IsMoving = VectorLenght != 0;
	
    if (!IsMoving)
    {
    	if (MovementStatus != Idle)
    	{
			Timer->SetTimer( ChangeToIdleStateDelegate, 2.5f);
    		SetMovementStatus(Stop);
    	}
    } else
    {
    	if (IsFalling)
    	{
    		if (IsFallingDown)
    		{
    			SetMovementStatus(Fall);
    		} else
    		{
    			SetMovementStatus(ECharacterMovementStatus::Jump);
    		}
    	} else
    	{
    		SetMovementStatus(Walk);
    	}
    }
}

void APersona::UpdateAnimationDirection(const FVector Velocity)
{
	const FVector VelocityNormalized = Velocity.GetSafeNormal();
	const float X = VelocityNormalized.X;
	const float Y = VelocityNormalized.Y;

	if (IsMoving)
	{
		if (Y > 0.0f && abs(X) < 0.25f)
		{
			SetAnimationDirection(Up);
		} else if (Y < 0.0f && abs(X) < 0.25f)
		{
			SetAnimationDirection(Down);
		} else if (X > 0.0f && abs(Y) < 0.25f)
		{
			SetAnimationDirection(Right);
		} else if (X < 0.0f && abs(Y) < 0.25f)
		{
			SetAnimationDirection(Left);
		}
	}
}

void APersona::Animate(float DeltaTime, FVector OldLocation, const FVector OldVelocity)
{
	UpdateMovementStatus(OldVelocity);
	UpdateAnimationDirection(OldVelocity);
}

void APersona::Flip()
{
	const float Rotation = AnimationDirection == Right ? 0.0f : 180.0f;
	GetSprite()->SetRelativeRotation(FRotator(0.0f, Rotation, 0.0f));
}

void APersona::ChangeToIdleState()
{
	const bool StillStopped = MovementStatus == Stop;
	
	if (StillStopped)
	{
		SetMovementStatus(Idle);
	}
}

void APersona::MoveAxisX(const float Value)
{
	if (CanMove)
	{
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
	}
}

void APersona::MoveAxisY(const float Value)
{
	if (CanMove)
	{
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
	}
}

void APersona::SetAnimationDirection(const TEnumAsByte<ECharacterAnimationDirection> Direction)
{
	AnimationDirection = Direction;
	OnAnimationDirectionUpdateDelegate.Broadcast();
}

void APersona::SetMovementStatus(const TEnumAsByte<ECharacterMovementStatus> Status)
{
	MovementStatus = Status;
	OnMovementStatusUpdateDelegate.Broadcast();
}

void APersona::PrintEnumerations() const
{
	const FString AnimationDirectionName = *UEnum::GetDisplayValueAsText(AnimationDirection).ToString();
	const FString MovementStatusName = *UEnum::GetDisplayValueAsText(MovementStatus).ToString();

	PRINT_STRING(AnimationDirectionName)
	PRINT_STRING(MovementStatusName)
}
