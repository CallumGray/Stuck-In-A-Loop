// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "HamsterController.generated.h"

class UScoreWidget;
class AEndGameCamera;

UCLASS()
class STUCKINALOOP_API AHamsterController : public APlayerController
{
	GENERATED_BODY()

	private:
	FTimerHandle RestartTimer;
	
	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess="true"))
	TSubclassOf<class UUserWidget> ScoreWidgetClass;

	UPROPERTY()
	UScoreWidget* ScoreWidget;

protected:
	virtual void BeginPlay() override;
	
public:
	void QueueRestartGame(float DelaySeconds);
	void SetScore(int32 InScore);
	int32 Score = 0;

	UPROPERTY()
	AEndGameCamera* EndGameCamera;
};
