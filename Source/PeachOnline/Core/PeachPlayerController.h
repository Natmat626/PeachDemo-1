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
	UPeachPlayerUI* PtrPlayerUI;
	
	UPROPERTY(BlueprintReadWrite)
	APeachPortal* Ptrportal=nullptr;

	UPROPERTY(BlueprintReadWrite)
	FString PlayerName = TEXT("");
	virtual void BeginPlay() override;

	UFUNCTION(NetMulticast,Reliable,WithValidation)
	void ServerShowKillerNotice(const FString&  Killer, const FString&  Bekillered);
	void ServerShowKillerNotice_Implementation( const FString&   Killer, const FString&   Bekillered);
	bool ServerShowKillerNotice_Validate(const FString&    Killer, const FString&    Bekillered);

	TSubclassOf<UKillerNotice> KillerNoticeClassUnit;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const override;
};
