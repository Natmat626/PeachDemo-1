// Fill out your copyright notice in the Description page of Project Settings.


#include "PeachPlayerController.h"

#include "BaseCharacter.h"
#include "PeachGameInstance.h"
#include "SaveName.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PeachOnline/PeachOnlineGameModeBase.h"
PRAGMA_DISABLE_OPTIMIZATION

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
	PlayerName = Cast<UPeachGameInstance>(GetWorld()->GetGameInstance())->PlayerName;
	PlayerName = TEXT("1111");
}







