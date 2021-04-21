// Fill out your copyright notice in the Description page of Project Settings.

#include "Mine.h"
#include "Hamster.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMine::AMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	MineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineMesh"));
	MineMesh->SetupAttachment(SceneComp);
}

// Called when the game starts or when spawned
void AMine::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this,&AMine::Detonate);
}

// Called every frame
void AMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMine::SetMineActive(bool Active)
{
	SetActorHiddenInGame(!Active);
	SetActorTickEnabled(Active);
	SetActorEnableCollision(Active);
}

void AMine::Detonate(AActor* ThisActor,AActor* OtherActor)
{
	AHamster* Hamster = Cast<AHamster>(OtherActor);
	if(!Hamster)return;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ExplosionParticle,GetActorLocation(),GetActorRotation(),true);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(),ExplosionSound,GetActorLocation(),GetActorRotation());
	SetMineActive(false);
	Hamster->Die(ExplosionStrength);	
}