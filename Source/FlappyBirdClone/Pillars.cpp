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
		UE_LOG(LogTemp, Warning, TEXT("Starting to Spawning Pillars"));
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &APillars::SpawnPillars, SpawnTime, true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Obsticles"));
	}
}

void APillars::SpawnPillars()
{
	// Spawn a new obsticle
	auto obsticle = Obsticles[FMath::FRandRange(0, Obsticles.Num()-1)];
	
	GetWorld()->SpawnActor<AObjectsBase>(obsticle, GetActorLocation(), GetActorRotation());
}
