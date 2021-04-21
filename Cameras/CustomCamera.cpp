#include "CustomCamera.h"
#include "Camera/CameraComponent.h"

ACustomCamera::ACustomCamera()
{
	GetCameraComponent()->bConstrainAspectRatio = false;
}

void ACustomCamera::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(
		this,0.f,EViewTargetBlendFunction::VTBlend_Linear,0.f,false);
}
