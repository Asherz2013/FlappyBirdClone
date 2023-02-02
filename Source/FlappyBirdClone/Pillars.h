// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectsBase.h"
#include "Pillars.generated.h"

UCLASS()
class FLAPPYBIRDCLONE_API APillars : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<TSubclassOf<AObjectsBase>> Obsticles;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float SpawnTime = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ObjectMoveSpeed = -200.0f;

	FTimerHandle SpawnTimerHandle;

	void SpawnPillars();

public:	
	// Sets default values for this actor's properties
	APillars();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
