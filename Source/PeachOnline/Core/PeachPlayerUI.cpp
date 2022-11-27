// Fill out your copyright notice in the Description page of Project Settings.


#include "PeachPlayerUI.h"

#include <iso646.h>

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
	ImagePortal_ToShow();
	ImagePortalAttack_ToHide();
	ImagePortalSkill_ToHide();

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
			TexBananaCount->SetText(FText::FromString(FString::FromInt(its->BananaCount*10)));
			TexAppleCount->SetText(FText::FromString(FString::FromInt(its->AppleCount*10)));
			TexWatermelonCount->SetText(FText::FromString(FString::FromInt(its->WatermelonCount*10)));
			
			BarRunEnergy->SetPercent(its->RunEnergy/100.f);

			if(its->PtrPortal==nullptr)
			{
				TipsCallback_ToHide();
				TipsEmermy_ToHide();
			}
			else if(its->PtrPortal!=nullptr)
			{
				if(its->PtrPortal->EmermyInzone>0)
				{
					TipsEmermy_ToShow();
				}
				else
				{
					TipsEmermy_ToHide();
				}
				if(its->PtrPortal->IsCanCallBack)
				{
					TipsCallback_ToShow();
				}
				else
				{
					TipsCallback_ToHide();
				}
			}
			
			if(its->PtrPortal==nullptr)
			{
				if(its->OrangeCount==0)
				{
					TexOrangeCount->SetText(FText::FromString(TEXT("未获得隐身传送门")));
				}
				else if(its->OrangeCount==1)
				{
					TexOrangeCount->SetText(FText::FromString(TEXT("获得隐身传送门-未放置")));
				}
				if(its->DurianCount==0)
				{
					TexDurianCount->SetText(FText::FromString(TEXT("未获得传人传送门")));
				}
				else if(its->DurianCount==1)
				{
					TexDurianCount->SetText(FText::FromString(TEXT("获得传人传送门-未放置")));
				}
			}

			else if(its->PtrPortal!=nullptr)
			{

				if(its->PtrPortal->CanOtherNotSee)
				{
					TexOrangeCount->SetText(FText::FromString(TEXT("获得隐身传送门-已放置")));
				}
				if(its->PtrPortal->CanTransmit)
				{
					TexDurianCount->SetText(FText::FromString(TEXT("获得传人传送门-已放置")));
				}
			}
			
			if(its->PtrPortal!=nullptr)
			{
				if(its->PtrPortal->CanTransmit==true)
				{
					ImagePortalSkill_ToShow();
				}
				else
				{
					ImagePortalSkill_ToHide();
				}
			}
			else
			{
				ImagePortalSkill_ToHide();
			}

			if(its->PtrPortal == nullptr and its->IsSetPortal ==false)
			{
				ImagePortal_ToShow();
			}
			else if(its->PtrPortal == nullptr and its->IsSetPortal == true)
			{
				ImagePortal_ReadyToPutPortal();
			}
			else
			{
				ImagePortal_ToHide();
			}

			if(its->PtrPortal!=nullptr)
			{
				if(its->RunEnergy>=20)
				{
					ImagePortalAttack_ToShow();
				}
				else
				{
					ImagePortalAttack_ToHide();
				}
			}
			else
			{
				ImagePortalAttack_ToHide();
			}
		}

	}
}


void UPeachPlayerUI::InitPlayerUI()
{
	TexBananaCount->SetText(FText::FromString(TEXT("0")));
	TexAppleCount->SetText(FText::FromString(TEXT("0")));
	TexWatermelonCount->SetText(FText::FromString(TEXT("0")));
	BarRunEnergy->SetPercent(1.f);
}
