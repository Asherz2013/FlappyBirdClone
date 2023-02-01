// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectsBase.h"
#include "ObjectPillar.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCLONE_API AObjectPillar : public AObjectsBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Setup");
	UStaticMeshComponent* TopPillar;

	UPROPERTY(EditAnywhere, Category = "Setup");
	UStaticMeshComponent* BottomPillar;

	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (UIMin = "0", UIMax = "4"))
	int32 PillarMaxScale = 4;


public:
	// Sets default values for this actor's properties
	AObjectPillar();
};
