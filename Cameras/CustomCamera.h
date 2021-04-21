// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "CustomCamera.generated.h"

UCLASS()
class STUCKINALOOP_API ACustomCamera : public ACameraActor
{
	GENERATED_BODY()

	public:

	ACustomCamera();
	virtual void BeginPlay() override;
};
