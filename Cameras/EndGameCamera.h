// Callum Gray, 2021

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"

#include "EndGameCamera.generated.h"

class AHamsterController;
/**
 * 
 */
UCLASS()
class STUCKINALOOP_API AEndGameCamera : public ACameraActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	AHamsterController* HamsterController;
	
protected:
	virtual void BeginPlay() override;

public:
	void SetAsCamera();

	UPROPERTY(EditAnywhere)
	float BlendTime = 3.f;
	
	UPROPERTY(EditAnywhere)
	float BlendExp = 1.f;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EViewTargetBlendFunction> BlendFunc = EViewTargetBlendFunction::VTBlend_Linear;
};
