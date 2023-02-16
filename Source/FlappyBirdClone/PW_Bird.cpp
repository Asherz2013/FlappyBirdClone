// Fill out your copyright notice in the Description page of Project Settings.


#include "PW_Bird.h"
#include "FlappyBirdCloneGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"
#include <Components/BoxComponent.h>

// Sets default values
APW_Bird::APW_Bird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(BoxCollider);

	// Tell the Box to NOT move in the following Axies
	BoxCollider->BodyInstance.bLockXTranslation = true;
	BoxCollider->BodyInstance.bLockYTranslation = true;
	// Tell the Box NOT to rotate
	BoxCollider->BodyInstance.bLockXRotation = true;
	BoxCollider->BodyInstance.bLockYRotation = true;
	BoxCollider->BodyInstance.bLockZRotation = true;
	BoxCollider->BodyInstance.bLockRotation = true;

	// Hook up the OnHitEvent
	BoxCollider->OnComponentHit.AddDynamic(this, &APW_Bird::OnMeshHit);
	// Tell the Mesh its needs to "Simulate Generated Events"
	BoxCollider->BodyInstance.bNotifyRigidBodyCollision = true;

	// Create the Static Mesh Component
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(BoxCollider);

	// Create the Spring Arm
	CameraBoon = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	// Attach to Mesh
	CameraBoon->SetupAttachment(BoxCollider);
	// Set default Boon Length
	CameraBoon->TargetArmLength = 600.f;
	CameraBoon->SocketOffset = FVector3d(0.f, 400.f, 0.f);

	// Create Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	// Attach to the Camera Boon, At the END of the Spring Arm, using the "Socket Name"
	Camera->SetupAttachment(CameraBoon, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void APW_Bird::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	PC->SetInputMode(FInputModeGameOnly());
	PC->bShowMouseCursor = false;

	// Get the GameMode
	GM_FPC = GetWorld()->GetAuthGameMode<AFlappyBirdCloneGameModeBase>();

	WdgOverlay = CreateWidget<UUserWidget>(GetGameInstance(), WidgetHUDClass);
	WdgOverlay->AddToViewport();
}

// Called every frame
void APW_Bird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GM_FPC->GetGameStarted())
	{
		// Tell the Box to Simulate Physics
		BoxCollider->SetSimulatePhysics(true);

		WdgOverlay->RemoveFromParent();
	}
}

// Called to bind functionality to input
void APW_Bird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Look to Change this to the new Enhanced Input System

	// Bind the "Jump" Input Action to this Pawn
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APW_Bird::Jump);
}

void APW_Bird::OnMeshHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	FString HitActorName = OtherActor->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *HitActorName);

	// Pause the game
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	PC->Pause();

	// Show the "Retry Widget"
	UUserWidget* WdgRetry = CreateWidget<UUserWidget>(GetGameInstance(), WidgetClass);
	WdgRetry->AddToViewport();

	PC->SetInputMode(FInputModeUIOnly());
	PC->bShowMouseCursor = true;
}

void APW_Bird::Jump()
{
	if (!GM_FPC->GetGameStarted())
	{
		GM_FPC->StartCountDown();
	}
	else
	{
		BoxCollider->BodyInstance.SetLinearVelocity(FVector::UpVector * JumpForce, false);
		SkeletalMesh->GetAnimInstance()->Montage_Play(Lift);
	}
}