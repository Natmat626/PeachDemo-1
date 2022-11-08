// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UFUNCTION(BlueprintImplementableEvent,Category="Health")
	void DeathMatchDeth(AActor* DamgeActor);
	
};
