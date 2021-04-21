// Callum Gray, 2021

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "MineRow.generated.h"

class AStuckInALoopGameModeBase;
class AMine;
class AHamsterController;
class AHamster;

UCLASS()
class STUCKINALOOP_API AMineRow : public AActor
{
	GENERATED_BODY()

private:
	
	//Counter for rotation since the top in radians
	float TopRotationRadians = 0.f;

	//Counter for rotation since the bottom in radians
	float BotRotationRadians = 0.f;

	void ShiftMines();

	UPROPERTY()
	TArray<AMine*> Mines;

	UPROPERTY()
	AStuckInALoopGameModeBase* LoopGameMode;

	UPROPERTY()
	AHamsterController* HamsterController;

	UPROPERTY()
	AHamster* Hamster;

	UPROPERTY(EditAnywhere)
	USoundBase* ScoreSound;
	
public:	
	// Sets default values for this actor's properties
	AMineRow();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMine> MineClass;	
		
	void SpawnMines();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Rotate, update score, 
	void RotateUpdate(float Radians);

};
