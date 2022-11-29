// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Engine/DataTable.h"
#include "KillerNotice.generated.h"

/**
 * 
 */
UCLASS()
class PEACHONLINE_API UKillerNotice : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TexKiller;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TexBekilled;
	
	FTimerHandle TimerHandle;
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct()override;
	void Destorythiswidget();


	float TableKillNoticeTime;
	UDataTable* Table;
};
