// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlappyBirdCloneGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FLAPPYBIRDCLONE_API AFlappyBirdCloneGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	UUserWidget* HUDClassWidget;

	int StartCountdown = 3;

	FTimerHandle CountdownTimerHandle;

	void CountDown();

protected:

	bool bGameStarted = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable)
	void GetGameText(FString& outGameText) const;


public:
	void StartCountDown();

	bool GetGameStarted() const;

};
