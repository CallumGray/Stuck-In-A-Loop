// Callum Gray, 2021

#include "MineRow.h"


#include "Hamster.h"
#include "HamsterController.h"
#include "Mine.h"
#include "StuckInALoopGameModeBase.h"
#include "Kismet/GameplayStatics.h"


AMineRow::AMineRow()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMineRow::BeginPlay()
{
	Super::BeginPlay();

	LoopGameMode = Cast<AStuckInALoopGameModeBase>(GetWorld()->GetAuthGameMode());
	HamsterController = Cast<AHamsterController>(GetWorld()->GetFirstPlayerController());

	if(!LoopGameMode)
	{
		UE_LOG(LogTemp,Error,TEXT("No LoopGameMode in MineRow"));
		return;
	}
	if(!HamsterController)
	{
		UE_LOG(LogTemp,Error,TEXT("No HamsterController in MineRow"));
		return;
	}

	Hamster = Cast<AHamster>(HamsterController->GetPawn());

	if(!Hamster)
	{
		UE_LOG(LogTemp,Error,TEXT("NO HAMSTER IN MINEROW"));
		return;
	}
	
	SpawnMines();
}

void AMineRow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMineRow::RotateUpdate(float Radians)
{
	//Don't do anything if the hamster is dead or doesn't exist
	if(!Hamster || Hamster->bDead)return;
	
	TopRotationRadians+=Radians;
	BotRotationRadians+=Radians;

	//Each time the row of mines reaches the top of the wheel, switch which mines are active 
	if(TopRotationRadians > 2.f*PI)
	{
		TopRotationRadians -= 2.f*PI;
		ShiftMines();
	}
	//Each time the row of mines reaches the bottom of the wheel, increment the score
	else if(BotRotationRadians > 1.1f*PI)
	{
		BotRotationRadians -= 2.f*PI;

		if(!HamsterController)return;
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(),ScoreSound,GetActorLocation(),GetActorRotation());
		HamsterController->SetScore(HamsterController->Score+1);
	}
}

void AMineRow::SpawnMines()
{
	if(!MineClass)
	{
		UE_LOG(LogTemp,Error,TEXT("NO MINE CLASS IN MINEROW"));
		return;
	}	
	if(!LoopGameMode)
	{
		UE_LOG(LogTemp,Error,TEXT("NO LOOP GAME MODE IN MINEROW"));
		return;
	}
	
	for(int32 i=-LoopGameMode->LanesEitherSide;i<=LoopGameMode->LanesEitherSide;i++)
	{	
		FVector SpawnLocation = GetActorRightVector()*i*LoopGameMode->LaneSpacing;
		FRotator SpawnRotation = FRotator::ZeroRotator;
		FActorSpawnParameters SpawnParams;

		AMine* Mine = GetWorld()->SpawnActor<AMine>(MineClass,SpawnLocation,SpawnRotation,SpawnParams);
		Mine->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
		Mines.Add(Mine);
	}

	ShiftMines();
}

void AMineRow::ShiftMines()
{
	if(Mines.Num()==0)return;
	
	//Shuffle the order of the mine pointers in the array
	for(int32 i=0;i<Mines.Num();i++)
	{
		int32 SwappedIndex = FMath::RandRange(i,Mines.Num()-1);
		if(i != SwappedIndex)Mines.Swap(i,SwappedIndex);
	}

	int32 ActiveMinesPerRow = FMath::Clamp(LoopGameMode->ActiveMinesPerRow,0,Mines.Num());
	//Set all mines inactive
	for(int32 i=0;i<Mines.Num();i++)Mines[i]->SetMineActive(false);
	//Enable the correct amount of mines
	for(int32 i=0;i<ActiveMinesPerRow;i++)Mines[i]->SetMineActive(true);
}