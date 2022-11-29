// Fill out your copyright notice in the Description page of Project Settings.


#include "PeachPlayerController.h"

#include "BaseCharacter.h"
#include "PeachGameInstance.h"
#include "SaveName.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "PeachOnline/PeachOnlineGameModeBase.h"
PRAGMA_DISABLE_OPTIMIZATION

APeachPlayerController::APeachPlayerController()
{
	KillerNoticeClassUnit = LoadClass<UKillerNotice>(nullptr,TEXT("WidgetBlueprint'/Game/UI/KillerNotice.KillerNotice_C'"));
}

void APeachPlayerController::OnNetCleanup(UNetConnection* Connection)
{
	if(UKismetSystemLibrary::IsServer(this))
	{
		auto it = Cast<APeachOnlineGameModeBase>(GetWorld()->GetAuthGameMode());

		if(Ptrportal!=nullptr)
		{
			Ptrportal->Destroy();
		}
		it->RemainPropNumber = it->RemainPropNumber+PropSum;
		Super::OnNetCleanup(Connection);
	}
}

void APeachPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//PlayerName = Cast<UPeachGameInstance>(GetWorld()->GetGameInstance())->PlayerName;
	PlayerName = TEXT("1111");
}

void APeachPlayerController::ServerShowKillerNotice_Implementation(const FString& Killer, const FString& Bekillered)
{
	if(this->PtrPlayerUI==nullptr)
	{
		return;
	}
	auto NewUnit =(CreateWidget<UKillerNotice>(this->PtrPlayerUI,KillerNoticeClassUnit));
	NewUnit->TexKiller->SetText(FText::FromString(*Killer));
	NewUnit->TexBekilled->SetText(FText::FromString(*Bekillered));
	this->PtrPlayerUI->KillerNoticeList->AddChild(NewUnit);
}

bool APeachPlayerController::ServerShowKillerNotice_Validate(const FString& Killer, const FString& Bekillered)
{
	return true;
}

void APeachPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(APeachPlayerController,PtrPlayerUI,COND_None);
}







