#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "StuckInALoopGameModeBase.generated.h"

UCLASS()
class STUCKINALOOP_API AStuckInALoopGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	protected:
	virtual void BeginPlay() override;

	public:
	AStuckInALoopGameModeBase();
	virtual void Tick(float DeltaSeconds) override;

	//Extra delay until the mines start spawning (in radians that the wheel must turn)
	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess="true",ClampMin=0.0),Category="Mines")
	float MineSpawnDelay = 0.f;
	
	//How many rows of mines are in one revolution of the wheel
	UPROPERTY(EditDefaultsOnly,Category="Mines")
	int32 RowsOfMines = 4;

	//Length from the centre of the wheel to mines
	UPROPERTY(EditAnywhere,Category="Mines")
	float MineRadius = 200.f;

	UPROPERTY(EditAnywhere,Category="Mines")
	int32 ActiveMinesPerRow = 2;

	//Max rotational speed of the wheel and mines in radians/sec
	UPROPERTY(EditAnywhere,Category="Wheel")
	float RotateSpeedMax = PI*0.5f;

	//Rotational acceleration of the wheel and mines in radians/sec^2
	UPROPERTY(EditAnywhere,Category="Wheel")
	float RotateAcceleration = PI*0.1f;

	//Number of lanes either side of the middle lane
	UPROPERTY(EditAnywhere,Category="Lanes")
	int32 LanesEitherSide = 1;

	//Spacing between each lane
	UPROPERTY(EditAnywhere,Category="Lanes")
	float LaneSpacing = 75.f;

	//Delay after the hamster has died before the game restarts
	UPROPERTY(EditAnywhere,Category="Gameplay Settings",meta=(ClampMin="0.0"))
	float EndGameDelaySeconds = 1.f;
};
