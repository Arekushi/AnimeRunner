#include "RunnerPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ARunnerPlayer::ARunnerPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Controller */ 
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	/* Spring Arm */
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->TargetArmLength = 700.0f;
	SpringArm->TargetOffset = FVector(0.0f, 0.0f, 200.0f);
	SpringArm->SetRelativeRotation(FRotator(-20.0f, -90.0f, 0.0f));
	
	/* SideView Camera */
	SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Side View Camera"));
	SideViewCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	SideViewCamera->bUsePawnControlRotation = false;
	SideViewCamera->bAutoActivate = true;
	// SideViewCamera->FieldOfView = 55.0f;
	// SideViewCamera->ProjectionMode = ECameraProjectionMode::Orthographic;
	// SideViewCamera->OrthoWidth = 2048.0f;

	/* PostProcess */
	FPostProcessSettings Settings = SideViewCamera->PostProcessSettings;
	Settings.DepthOfFieldFocalDistance = SpringArm->TargetArmLength;
	SideViewCamera->PostProcessSettings = Settings;
	
	/* Movement */
	UCharacterMovementComponent* CharacterMov = GetCharacterMovement();
	CharacterMov->bUseControllerDesiredRotation = true;
}

void ARunnerPlayer::BeginPlay()
{
	Super::BeginPlay();
	InputEnabled = true;
}

void ARunnerPlayer::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARunnerPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/* Movement Controllers */
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("Axis X", this, &ARunnerPlayer::MoveAxisX);
	PlayerInputComponent->BindAxis("Axis Y", this, &ARunnerPlayer::MoveAxisY);
}

// void APlayer::UpdateSpriteDirection()
// {
// 	const FVector Velocity = GetVelocity();
// 	const float X = Velocity.X;
// 	const bool NeedToFlipRight = X > 0.0f && !IsFacingToRight;
// 	const bool NeedToFlipLeft = X < 0.0f && IsFacingToRight;
//
// 	if (NeedToFlipRight || NeedToFlipLeft)
// 	{
// 		Flip();
// 	}
// }

void ARunnerPlayer::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// if (OtherActor != nullptr)
	// {
	// 	CanMove = false;
	// }
}

APlayerController* ARunnerPlayer::GetPlayerController() const
{
	return UGameplayStatics::GetPlayerController(this, 0);
}

void ARunnerPlayer::ToggleInput()
{
	APlayerController* PlayerController = GetPlayerController();

	if (InputEnabled)
	{
		DisableInput(PlayerController);
	} else
	{
		EnableInput(PlayerController);
	}

	InputEnabled = !InputEnabled;
}
