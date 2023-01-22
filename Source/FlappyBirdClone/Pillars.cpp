// Fill out your copyright notice in the Description page of Project Settings.


#include "Pillars.h"

// Sets default values
APillars::APillars()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		smc->SetMobility(EComponentMobility::Movable);
		smc->SetupAttachment(RootComponent);
		smc->SetWorldLocation(GetActorLocation() + FVector(0, PillarGap * i, 0));
		smc->SetStaticMesh(PillarMesh);
		smc->SetWorldScale3D(FVector(1, 1, FMath::RandRange(1, 4)));

		Pillars.Add(smc);
	}
}

// Called every frame
void APillars::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

