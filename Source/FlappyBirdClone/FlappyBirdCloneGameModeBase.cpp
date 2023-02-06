// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdCloneGameModeBase.h"


void AFlappyBirdCloneGameModeBase::BeginPlay()
{
	bGameStarted = false;
}

bool AFlappyBirdCloneGameModeBase::GetGameStarted() const
{
	return bGameStarted;
}

void AFlappyBirdCloneGameModeBase::GetGameText(FString& outGameText) const
{
	if (!CountdownTimerHandle.IsValid())
	{
		outGameText = "Press 'Jump' to Start";
	}
	else
	{
		outGameText = FString::FromInt(StartCountdown);
	}
}

void AFlappyBirdCloneGameModeBase::StartCountDown()
{
	if (!CountdownTimerHandle.IsValid())
	{
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AFlappyBirdCloneGameModeBase::CountDown, 1, true);
	}
}

void AFlappyBirdCloneGameModeBase::CountDown()
{
	StartCountdown--;

	//UE_LOG(LogTemp, Warning, TEXT("GM CountDown: %i"), StartCountdown);

	if (StartCountdown == 0)
	{
		bGameStarted = true;

		GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
	}
}