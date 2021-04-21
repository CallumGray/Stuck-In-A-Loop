#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Hamster.generated.h"

class AStuckInALoopGameModeBase;
UCLASS()
class STUCKINALOOP_API AHamster : public ACharacter
{
	GENERATED_BODY()

private:
	void Left();
	void Right();
	void SideStep(bool Right);

	UPROPERTY()
	AStuckInALoopGameModeBase* LoopGameMode; 

	//Which lane the hamster is in
	int32 CurrentLane;

	//Lanes which the hamster will interpolate between
	TArray<FVector> Lanes;

	//Calculate the lanes
	void CalculateLanes();

	//How quickly the Hamster sidesteps
	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess="true"))
	float SidestepInterpSpeed = 7.5f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	AHamster();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Die(float ExplosionStrength);

	UPROPERTY(BlueprintReadWrite)
	bool bDead = false;

	UPROPERTY(BlueprintReadWrite)
	float RunAlpha = 0.f;
};
