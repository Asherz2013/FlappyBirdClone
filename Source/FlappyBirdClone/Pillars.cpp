// Fill out your copyright notice in the Description page of Project Settings.

#include "Pillars.h"
#include "FlappyBirdCloneGameModeBase.h"

#include "ObjectsBase.h"

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

	// Get the GameMode
	GM_FPC = GetWorld()->GetAuthGameMode<AFlappyBirdCloneGameModeBase>();
}

void APillars::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GM_FPC->GetGameStarted())
	{
		if (!Obsticles.IsEmpty() && !SpawnTimerHandle.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Starting to Spawning Pillars"));
			GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &APillars::SpawnPillars, SpawnTime, true);
		}
	}
	else if (SpawnTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	}
}

void APillars::SpawnPillars()
{
	// Spawn a new obsticle
	auto obsticle = Obsticles[FMath::FRandRange(0.f, (float)Obsticles.Num()-1)];
	
	AObjectsBase* SpawnObj = GetWorld()->SpawnActor<AObjectsBase>(obsticle, GetActorLocation(), GetActorRotation());
	SpawnObj->SetSpeed(ObjectMoveSpeed);
}
