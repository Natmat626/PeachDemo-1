// Fill out your copyright notice in the Description page of Project Settings.


#include "PeachPlayerUI.h"

#include "BaseCharacter.h"


void UPeachPlayerUI::NativeConstruct()
{
	Super::NativeConstruct();
	TexBananaCount->SetText(FText::FromString(TEXT("0")));
	TexAppleCount->SetText(FText::FromString(TEXT("0")));
	TexWatermelonCount->SetText(FText::FromString(TEXT("0")));
	TexOrangeCount->SetText(FText::FromString(TEXT("0")));
	TexDurianCount->SetText(FText::FromString(TEXT("0")));
	BarRunEnergy->SetPercent(1.f);

}

void UPeachPlayerUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	auto it = GetWorld()->GetFirstPlayerController();

	if(it!=nullptr)
	{
		auto its = Cast<ABaseCharacter>(it->GetPawn());
		if(its!=nullptr)
		{
			TexBananaCount->SetText(FText::FromString(FString::FromInt(its->BananaCount)));
			TexAppleCount->SetText(FText::FromString(FString::FromInt(its->AppleCount)));
			TexWatermelonCount->SetText(FText::FromString(FString::FromInt(its->WatermelonCount)));
			TexOrangeCount->SetText(FText::FromString(FString::FromInt(its->OrangeCount)));
			TexDurianCount->SetText(FText::FromString(FString::FromInt(its->DurianCount)));
			BarRunEnergy->SetPercent(its->RunEnergy/100.f);

		}

	}
}


void UPeachPlayerUI::InitPlayerUI()
{
	TexBananaCount->SetText(FText::FromString(TEXT("0")));
	TexAppleCount->SetText(FText::FromString(TEXT("0")));
	TexWatermelonCount->SetText(FText::FromString(TEXT("0")));
	TexOrangeCount->SetText(FText::FromString(TEXT("0")));
	TexDurianCount->SetText(FText::FromString(TEXT("0")));
	BarRunEnergy->SetPercent(1.f);
}
