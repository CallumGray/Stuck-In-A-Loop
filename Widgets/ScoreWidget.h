// Callum Gray, 2021

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

class UTextBlock;

UCLASS()
class STUCKINALOOP_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetScoreWidget(int32 Score) const;
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* FrontScore;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* BackScore;
};