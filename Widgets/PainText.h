// Callum Gray, 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PainText.generated.h"

UCLASS()
class STUCKINALOOP_API APainText : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APainText();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
