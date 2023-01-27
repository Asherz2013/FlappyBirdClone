// Fill out your copyright notice in the Description page of Project Settings.


#include "PW_Bird.h"

// Sets default values
APW_Bird::APW_Bird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Static Mesh Component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// Make the mesh the root component
	SetRootComponent(Mesh);
	// Tell the Mesh to NOT move in the following Axies
	Mesh->BodyInstance.bLockXTranslation = true;
	Mesh->BodyInstance.bLockYTranslation = true;
	// Tell the Mesh NOT to rotate
	Mesh->BodyInstance.bLockXRotation = true;
	Mesh->BodyInstance.bLockYRotation = true;
	Mesh->BodyInstance.bLockZRotation = true;
	Mesh->BodyInstance.bLockRotation = true;
	// Hook up the OnHitEvent
	Mesh->OnComponentHit.AddDynamic(this, &APW_Bird::OnMeshHit);
	// Tell the Mesh its needs to "Simulate Generated Events"
	Mesh->BodyInstance.bNotifyRigidBodyCollision = true;

	// Create the Spring Arm
	CameraBoon = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	// Attach to Mesh
	CameraBoon->SetupAttachment(Mesh);
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
	
	// Tell the Mesh to Simulate Physics
	Mesh->SetSimulatePhysics(true);

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	PC->SetInputMode(FInputModeGameOnly());
	PC->bShowMouseCursor = false;

}

// Called every frame
void APW_Bird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	UE_LOG(LogTemp, Warning, TEXT("%s"), *HitActorName);

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
	UE_LOG(LogTemp, Warning, TEXT("JUMP"));
	Mesh->BodyInstance.SetLinearVelocity(FVector::UpVector * JumpForce, false);
}
