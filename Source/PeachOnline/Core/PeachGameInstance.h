// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PeachGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PEACHONLINE_API UPeachGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString PlayerName=TEXT("");
};
