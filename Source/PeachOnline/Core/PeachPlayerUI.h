// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "PeachPlayerUI.generated.h"

/**
 * 
 */
UCLASS()
class PEACHONLINE_API UPeachPlayerUI : public UUserWidget
{
	GENERATED_BODY()
public:
	
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

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* KillerNoticeList;
	void InitPlayerUI();
public:
	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	UFUNCTION(BlueprintImplementableEvent)
	void ImagePortal_ToShow();

	UFUNCTION(BlueprintImplementableEvent)
	void ImagePortal_ToHide();

	UFUNCTION(BlueprintImplementableEvent)
	void ImagePortal_ReadyToPutPortal();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ImagePortalAttack_ToShow();

	UFUNCTION(BlueprintImplementableEvent)
	void ImagePortalAttack_ToHide();

	UFUNCTION(BlueprintImplementableEvent)
	void ImagePortalSkill_ToShow();

	UFUNCTION(BlueprintImplementableEvent)
	void ImagePortalSkill_ToHide();

	UFUNCTION(BlueprintImplementableEvent)
	void TipsEmermy_ToShow();

	UFUNCTION(BlueprintImplementableEvent)
	void TipsEmermy_ToHide();

	UFUNCTION(BlueprintImplementableEvent)
	void TipsCallback_ToShow();

	UFUNCTION(BlueprintImplementableEvent)
	void TipsCallback_ToHide();

	UFUNCTION(BlueprintImplementableEvent)
	void Aiming_ToShow();

	UFUNCTION(BlueprintImplementableEvent)
	void Aiming_ToHide();
	
};
