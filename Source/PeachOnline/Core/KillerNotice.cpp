// Fill out your copyright notice in the Description page of Project Settings.


#include "KillerNotice.h"

#include "PeachPlayerController.h"

void UKillerNotice::NativeConstruct()
{
	Super::NativeConstruct();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UKillerNotice::Destorythiswidget, 5.0f, false);
}

void UKillerNotice::Destorythiswidget()
{
	if(this!=nullptr)
	{
		Cast<APeachPlayerController>(GetWorld()->GetFirstPlayerController())->PtrPlayerUI->KillerNoticeList->ClearChildren();
	}
}
