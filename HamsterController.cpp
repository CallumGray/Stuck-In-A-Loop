// Fill out your copyright notice in the Description page of Project Settings.


#include "HamsterController.h"

#include "Cameras/EndGameCamera.h"
#include "Widgets/ScoreWidget.h"

void AHamsterController::BeginPlay()
{
	if(!ScoreWidgetClass)
	{
		UE_LOG(LogTemp,Error,TEXT("NO SCORE WIDGET CLASS"));
		return;
	}
	
	//Display the score widget
	ScoreWidget = Cast<UScoreWidget>(CreateWidget(this,ScoreWidgetClass,TEXT("ScoreWidget")));
	if(ScoreWidget)ScoreWidget->AddToViewport();
}

void AHamsterController::SetScore(int32 InScore)
{
	Score = InScore;

	if(!ScoreWidget)
	{
		UE_LOG(LogTemp,Warning,TEXT("No ScoreWidget in HamsterController"));
		return;
	}

	ScoreWidget->SetScoreWidget(Score);
}

void AHamsterController::QueueRestartGame(float DelaySeconds)
{
	if(!GetWorldTimerManager().IsTimerActive(RestartTimer))
		GetWorldTimerManager().SetTimer(RestartTimer,this,&APlayerController::RestartLevel,DelaySeconds);

	if(!EndGameCamera)
	{
		UE_LOG(LogTemp,Error,TEXT("NO ENDGAMECAMERA IN LEVEL"));
		return;
	}

	EndGameCamera->SetAsCamera();
}