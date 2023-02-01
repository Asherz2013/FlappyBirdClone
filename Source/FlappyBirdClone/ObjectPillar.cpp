// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPillar.h"

AObjectPillar::AObjectPillar()
{
    // Create Top Pillar
    TopPillar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top Pillar"));
    // Attach to Root and tell it to be mobile
    TopPillar->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    TopPillar->SetMobility(EComponentMobility::Movable);

	// Tell the Mesh to NOT move in the following Axies
	TopPillar->BodyInstance.bLockXTranslation = true;
	TopPillar->BodyInstance.bLockYTranslation = true;
	// Tell the TopPillar NOT to rotate
	TopPillar->BodyInstance.bLockXRotation = true;
	TopPillar->BodyInstance.bLockYRotation = true;
	TopPillar->BodyInstance.bLockZRotation = true;
	TopPillar->BodyInstance.bLockRotation = true;

	// Create the Bottom Pillar
	BottomPillar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottom Pillar"));
	// Attach to Root and tell it to be mobile
	BottomPillar->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	BottomPillar->SetMobility(EComponentMobility::Movable);

	// Tell the Mesh to NOT move in the following Axies
	BottomPillar->BodyInstance.bLockXTranslation = true;
	BottomPillar->BodyInstance.bLockYTranslation = true;
	// Tell the BottomPillar NOT to rotate
	BottomPillar->BodyInstance.bLockXRotation = true;
	BottomPillar->BodyInstance.bLockYRotation = true;
	BottomPillar->BodyInstance.bLockZRotation = true;
	BottomPillar->BodyInstance.bLockRotation = true;
}
