
#include "Hamster.h"


#include "HamsterController.h"
#include "StuckInALoopGameModeBase.h"
#include "Components/CapsuleComponent.h"

AHamster::AHamster()
{
 	PrimaryActorTick.bCanEverTick = true;

	//Allows hamster to be rotated about z
	bUseControllerRotationYaw = false;
}

void AHamster::BeginPlay()
{
	Super::BeginPlay();

	LoopGameMode = Cast<AStuckInALoopGameModeBase>(GetWorld()->GetAuthGameMode());

	if(!LoopGameMode)
	{
		UE_LOG(LogTemp,Warning,TEXT("No LoopGameMode in Hamster"));
		return;
	}
	
	CalculateLanes();
}

void AHamster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Lanes.Num() > CurrentLane)
	{
		FVector NewLocation = FVector(
        FMath::FInterpTo(GetActorLocation().X,Lanes[CurrentLane].X,DeltaTime,SidestepInterpSpeed),
        FMath::FInterpTo(GetActorLocation().Y,Lanes[CurrentLane].Y,DeltaTime,SidestepInterpSpeed),
        GetActorLocation().Z		
        );

		SetActorLocation(NewLocation);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("LANE OUT OF BOUNDS!!"));
	}
}

void AHamster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Left"),EInputEvent::IE_Pressed,this,&AHamster::Left);
	PlayerInputComponent->BindAction(TEXT("Right"),EInputEvent::IE_Pressed,this,&AHamster::Right);
}

void AHamster::Die(float ExplosionStrength)
{
	if(!bDead)
	{
		bDead = true;
		AHamsterController* HamsterController = Cast<AHamsterController>(Controller);
		HamsterController->QueueRestartGame(LoopGameMode->EndGameDelaySeconds);

		//Disable main collision
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		//Enable ragdoll (and let the ragdoll overlap the mines)
		GetMesh()->SetGenerateOverlapEvents(true);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetMesh()->SetSimulatePhysics(true);
	}
	
	//Launch (could change this to use the surface normal?)
	if(GetMesh()->IsSimulatingPhysics())GetMesh()->AddImpulse(FVector::UpVector*ExplosionStrength);
}

void AHamster::Left()
{
	SideStep(false);
}

void AHamster::Right()
{
	SideStep(true);
}

void AHamster::SideStep(bool Right)
{
	if(!bDead)
	{
		int32 NewLane = CurrentLane+(Right ? 1 : -1);
		CurrentLane = FMath::Clamp(NewLane,0,Lanes.Num()-1);	
	}
}

void AHamster::CalculateLanes()
{	
	FVector Origin = GetActorLocation();

	//Add points to the array ordered from left to right
	for(int32 i=-LoopGameMode->LanesEitherSide;i<=LoopGameMode->LanesEitherSide;i++)
	{
		FVector NewLane = Origin+GetActorRightVector()*i*LoopGameMode->LaneSpacing;
		Lanes.Add(NewLane);
	}

	CurrentLane = Lanes.Num()/2;
}
