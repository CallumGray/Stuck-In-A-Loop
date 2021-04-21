// Fill out your copyright notice in the Description page of Project Settings.

#include "Wheel.h"
#include "Hamster.h"
#include "HamsterController.h"
#include "MineRow.h"
#include "StuckInALoopGameModeBase.h"

// Sets default values
AWheel::AWheel()
{
 	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;
	
	WheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelMesh"));
	WheelMesh->SetupAttachment(SceneComp);
}

void AWheel::BeginPlay()
{
	Super::BeginPlay();

	InitialRotation = GetActorRotation();
	
	LoopGameMode = Cast<AStuckInALoopGameModeBase>(GetWorld()->GetAuthGameMode());
	HamsterController = Cast<AHamsterController>(GetWorld()->GetFirstPlayerController());
	Hamster = Cast<AHamster>(HamsterController->GetPawn());
	
	if(!LoopGameMode)
	{
		UE_LOG(LogTemp,Error,TEXT("NO LOOP GAME MODE IN WHEEL"));
		return;
	}

	if(!HamsterController)
	{
		UE_LOG(LogTemp,Warning,TEXT("NO HAMSTER CONTROLLER IN WHEEL"));
		return;
	}

	if(!Hamster)
	{
		UE_LOG(LogTemp,Warning,TEXT("NO HAMSTER IN WHEEL"));
		return;
	}

	MineRowSpacing = 2.f*PI/LoopGameMode->RowsOfMines;
}

void AWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccelerateRotation(DeltaTime);
}

void AWheel::AccelerateRotation(float DeltaTime)
{
	if(!LoopGameMode)return;

	//Apply acceleration
	CurrentRotateSpeed = FMath::Clamp(CurrentRotateSpeed + LoopGameMode->RotateAcceleration * DeltaTime,0.f,LoopGameMode->RotateSpeedMax);
	const float RotationThisTick = CurrentRotateSpeed*DeltaTime;
	
	//rotate by speed
	AddActorLocalRotation(FQuat(FVector::RightVector,RotationThisTick));
	RotatedRadians += RotationThisTick;

	//Don't spawn any more mines if the hamster is dead
	if(Hamster->bDead)return;

	//Set the hamster's animation to be based on the wheel's rotation speed
	Hamster->RunAlpha = CurrentRotateSpeed/LoopGameMode->RotateSpeedMax;
	
	if(MineRows.Num() < LoopGameMode->RowsOfMines)
	{
		if(RotatedRadians > LoopGameMode->MineSpawnDelay)
		{
			SpawnMineRow();
			RotatedRadians-=MineRowSpacing;
		}
	}

	for(AMineRow* MineRow : MineRows)MineRow->RotateUpdate(RotationThisTick);
}

void AWheel::SpawnMineRow()
{
	if(!MineRowClass)
	{
		UE_LOG(LogTemp,Error,TEXT("NO MINEROW CLASS IN WHEEL"));
		return;
	}

	FVector LocalLocation = FVector::UpVector*LoopGameMode->MineRadius;
	FQuat MineRelativeRotation = FQuat(FVector::LeftVector,LoopGameMode->MineSpawnDelay+MineRows.Num()*MineRowSpacing);
	FVector MineRelativeLocation = MineRelativeRotation.RotateVector(LocalLocation);
	FActorSpawnParameters SpawnParams;

	//Rotation to make the mines face inward
	MineRelativeRotation *= FQuat(FVector::LeftVector,PI);

	//Spawn the mine and attach it to this wheel
	AMineRow* MineRow = GetWorld()->SpawnActor<AMineRow>(
            MineRowClass,MineRelativeLocation,FRotator(MineRelativeRotation),SpawnParams);
	MineRow->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
	MineRows.Add(MineRow);	
}