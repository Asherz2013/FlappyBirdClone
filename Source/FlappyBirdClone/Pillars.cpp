// Fill out your copyright notice in the Description page of Project Settings.


#include "Pillars.h"

// Sets default values
APillars::APillars()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APillars::BeginPlay()
{
	Super::BeginPlay();

	// Only run the timer if we have some Obsticles to spawn
	if (!Obsticles.IsEmpty())
	{
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &APillars::SpawnPillars, SpawnTime, true);
	}
}

void APillars::OnConstruction(const FTransform &Transform)
{
	Super::OnConstruction(Transform);

}

void APillars::SpawnPillars()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning Pillars"));
	
	// Spawn a new obsticle
	AObjectsBase* obsticle = Obsticles[FMath::FRandRange(0, Obsticles.Num()-1)];
		
	//GetWorld()->SpawnActor<AObjectsBase>(obsticle);
}
