#include "RunnerPlayer.h"

#include "AnimeRunner/RunnerPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#define PRINT(String) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, String);

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
	bGoToMenu = false;
	
	OnDestroyed.AddDynamic(this, &ARunnerPlayer::OnDestroyPlayer);
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

void ARunnerPlayer::TakeDamage(const int Damage)
{
	HP -= Damage;

	if (HP <= 0)
	{
		const ARunnerPlayerController* PlayerController = Cast<ARunnerPlayerController>(GetPlayerController());

		if (PlayerController)
		{
			PlayerController->OnDeathDelegate.Broadcast();
		}
	}
}

void ARunnerPlayer::OnDestroyPlayer(AActor* DestroyedActor)
{
	if (!bGoToMenu)
	{
		TakeDamage(1);
	}
}
