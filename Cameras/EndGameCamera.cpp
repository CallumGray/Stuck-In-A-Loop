// Callum Gray, 2021

#include "EndGameCamera.h"
#include "StuckInALoop/HamsterController.h"

void AEndGameCamera::BeginPlay()
{
	HamsterController = Cast<AHamsterController>(GetWorld()->GetFirstPlayerController());

	if(!HamsterController)
	{
		UE_LOG(LogTemp,Error,TEXT("NO HAMSTER CONTROLLER IN ENDGAMECAMERA"));
		return;
	}

	HamsterController->EndGameCamera = this;
}

void AEndGameCamera::SetAsCamera()
{
	HamsterController->SetViewTargetWithBlend(
        this,BlendTime,BlendFunc,BlendExp,false);
}




