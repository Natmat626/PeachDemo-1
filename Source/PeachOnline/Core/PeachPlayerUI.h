// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "PeachPlayerUI.generated.h"

/**
 * 
 */
UCLASS()
class PEACHONLINE_API UPeachPlayerUI : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TexBananaCount;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TexAppleCount;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TexWatermelonCount;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TexOrangeCount;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TexDurianCount;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* BarRunEnergy;

	void InitPlayerUI();
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
