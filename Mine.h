// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Mine.generated.h"

UCLASS()
class STUCKINALOOP_API AMine : public AActor
{
	GENERATED_BODY()

private:
	

public:	
	// Sets default values for this actor's properties
	AMine();

	UPROPERTY()
	USceneComponent* SceneComp;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MineMesh;

	UPROPERTY(EditAnywhere,Category="Explosion")
	UParticleSystem* ExplosionParticle;

	UPROPERTY(EditAnywhere,Category="Explosion")
	USoundBase* ExplosionSound;

	UFUNCTION()
	void Detonate(AActor* ThisActor,AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	float ExplosionStrength = 100000.f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetMineActive(bool Active);
};
