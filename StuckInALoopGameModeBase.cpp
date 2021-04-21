#include "StuckInALoopGameModeBase.h"


#include "Hamster.h"
#include "MineRow.h"
#include "Wheel.h"

AStuckInALoopGameModeBase::AStuckInALoopGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AStuckInALoopGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AStuckInALoopGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
