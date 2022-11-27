// Fill out your copyright notice in the Description page of Project Settings.


#include "KillerNotice.h"

void UKillerNotice::NativeConstruct()
{
	Super::NativeConstruct();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UKillerNotice::Destoryself, 5.0f, false);
}

void UKillerNotice::Destoryself()
{
	if(this!=nullptr)
	{
		Destoryself();
	}
}
