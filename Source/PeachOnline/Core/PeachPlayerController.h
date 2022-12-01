// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KillerNotice.h"
#include "PeachPlayerUI.h"
#include "PeachPortal.h"
#include "GameFramework/PlayerController.h"
#include "PeachPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PEACHONLINE_API APeachPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	APeachPlayerController();
	UFUNCTION(BlueprintImplementableEvent,Category="Health")
	void DeathMatchDeth(AActor* DamgeActor);
	virtual void OnNetCleanup(class UNetConnection* Connection) override;

	UPROPERTY(BlueprintReadWrite)
	int PropSum=0;

	UPROPERTY(BlueprintReadWrite,Replicated)
	int Playerid=0;
	UPROPERTY(BlueprintReadWrite,Replicated)
	UPeachPlayerUI* PtrPlayerUI;
	
	UPROPERTY(BlueprintReadWrite)
	APeachPortal* Ptrportal=nullptr;

	UPROPERTY(BlueprintReadWrite,Replicated)
	FString PlayerName = TEXT("");
	virtual void BeginPlay() override;

	
	UFUNCTION(BlueprintCallable)
	int GetPlayerNetIndex();
	
	TSubclassOf<UKillerNotice> KillerNoticeClassUnit;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const override;
};
