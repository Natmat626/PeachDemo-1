// Fill out your copyright notice in the Description page of Project Settings.


#include "KillerNotice.h"

#include "BaseCharacter.h"
#include "PeachPlayerController.h"
#include "Engine/DataTable.h"

void UKillerNotice::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Table = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/DesignerTable/DesignerTable.DesignerTable'"));
}

void UKillerNotice::NativeConstruct()
{
	Super::NativeConstruct();

	if (Table != nullptr)
	{
		for (auto it : Table->GetRowMap())
		{
			FString rowName = (it.Key).ToString();
			//FProduct为你的FStruct
			FDatas* pRow = (FDatas*)it.Value;
			//输出需根据你的FStruct进行调整
			if(pRow->PropertyName==TEXT("TableKillNoticeTime"))
			{
				TableKillNoticeTime=pRow->Value;
				break;
			}
		}
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UKillerNotice::Destorythiswidget, TableKillNoticeTime, false);
}

void UKillerNotice::Destorythiswidget()
{
	if(this!=nullptr)
	{
		Cast<APeachPlayerController>(GetWorld()->GetFirstPlayerController())->PtrPlayerUI->KillerNoticeList->ClearChildren();
	}
}
