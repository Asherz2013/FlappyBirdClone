// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectsBase.generated.h"

UCLASS(abstract)
class FLAPPYBIRDCLONE_API AObjectsBase : public AActor
{
	GENERATED_BODY()

private:
	float m_Speed;

protected:
	USceneComponent* Root;
	
public:	
	// Sets default values for this actor's properties
	AObjectsBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSpeed(float speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
