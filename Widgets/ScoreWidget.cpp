// Callum Gray, 2021

#include "ScoreWidget.h"
#include "Components/TextBlock.h"

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetScoreWidget(0);
}

void UScoreWidget::SetScoreWidget(int32 Score) const
{
	if(FrontScore)FrontScore->SetText(FText::AsNumber(Score));
	if(BackScore)BackScore->SetText(FText::AsNumber(Score));
}