// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pillars.generated.h"

UCLASS()
class FLAPPYBIRDCLONE_API APillars : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	TArray<UStaticMeshComponent*> Pillars;

	UPROPERTY(EditAnywhere, Category = "Setup")
	int NumOfPillars = 10;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float PillarGap = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MoveSpeed = -200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UStaticMesh* PillarMesh;

	UFUNCTION(BluePrintCallable, Category = "On Construction")
	void SpawnPillars();

	USceneComponent* Root;

public:	
	// Sets default values for this actor's properties
	APillars();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when an instance of this class is placed (in editor) or spawned.
	virtual void OnConstruction(const FTransform &Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
