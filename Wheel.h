#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wheel.generated.h"

class AHamsterController;
class AMineRow;
class AStuckInALoopGameModeBase;
class AHamster;

UCLASS()
class STUCKINALOOP_API AWheel : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMineRow> MineRowClass;

	UPROPERTY()
	TArray<AMineRow*> MineRows;
	
	float MineRowSpacing;
	
	FRotator InitialRotation;
	float CurrentRotateSpeed = 0.f;

	//How much the wheel has rotated
	float RotatedRadians = 0.f;
	
	UPROPERTY()
	AStuckInALoopGameModeBase* LoopGameMode;

	UPROPERTY()
	AHamsterController* HamsterController;

	UPROPERTY()
	AHamster* Hamster;
	
	void SpawnMineRow();
	
protected:
	virtual void BeginPlay() override;

public:
	AWheel();
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	USceneComponent* SceneComp;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* WheelMesh;

	void AccelerateRotation(float DeltaTime);
};
