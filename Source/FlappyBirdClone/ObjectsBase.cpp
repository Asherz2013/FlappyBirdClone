// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectsBase.h"

// Sets default values
AObjectsBase::AObjectsBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

// Called when the game starts or when spawned
void AObjectsBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObjectsBase::SetSpeed(float speed)
{
	m_Speed = speed;
}

// Called every frame
void AObjectsBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector location = GetActorLocation();

	// Set the position of this Actor to be "moving" based on Dealta Time and a Speed
	SetActorLocation(location + FVector(0, m_Speed * DeltaTime, 0));
}

