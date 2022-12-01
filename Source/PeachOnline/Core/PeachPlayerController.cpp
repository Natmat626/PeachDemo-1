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
	//PlayerName = TEXT("1111");
}

int APeachPlayerController::GetPlayerNetIndex()
{
	return Playerid;
}

void APeachPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(APeachPlayerController,PtrPlayerUI,COND_None);
	DOREPLIFETIME_CONDITION(APeachPlayerController,PlayerName,COND_None);
	DOREPLIFETIME_CONDITION(APeachPlayerController,Playerid,COND_None);
}







