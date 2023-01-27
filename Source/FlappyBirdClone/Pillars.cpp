// Fill out your copyright notice in the Description page of Project Settings.


#include "Pillars.h"

// Sets default values
APillars::APillars()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

// Called when the game starts or when spawned
void APillars::BeginPlay()
{
	Super::BeginPlay();

}

void APillars::OnConstruction(const FTransform &Transform)
{
	Super::OnConstruction(Transform);

	// Only Spawn Mesh's IF we have a Mesh to spawn
	if (PillarMesh)
	{
		SpawnPillars();
	}
}

void APillars::SpawnPillars()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning Pillars"));
	
	Pillars.Empty(NumOfPillars);
	
	for (size_t i = 0; i < NumOfPillars; i++)
	{
		// Create a new Static Mesh Components
		UStaticMeshComponent* smc = (UStaticMeshComponent*)AddComponentByClass(UStaticMeshComponent::StaticClass(), true, FTransform(), true);

		smc->RegisterComponent();
		smc->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		smc->SetMobility(EComponentMobility::Movable);

		smc->SetWorldLocation(GetActorLocation() + FVector(0, PillarGap * i, 0));
		smc->SetStaticMesh(PillarMesh);
		smc->SetWorldScale3D(FVector(1, 1, FMath::RandRange(1, PillarMaxScale)));

		Pillars.Add(smc);
	}
}

// Called every frame
void APillars::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Set the position of this Actor to be "moving" based on Dealta Time and a Speed
	SetActorLocation(GetActorLocation() + FVector(0, MoveSpeed * DeltaTime, 0));

	// Once we are of screen, move back to the beginning
	if (GetActorLocation().Y < -1 * ((PillarGap * NumOfPillars) + 400.f))
	{
		SetActorLocation(GetActorLocation() + FVector(0, PillarGap * NumOfPillars + 1000.f, 0));
	}
}

