// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/PeachProp.h"
#include "GameFramework/GameModeBase.h"
#include "PeachOnlineGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PEACHONLINE_API APeachOnlineGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UObject*> PropPonits;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MaxPropPointsIndex;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int RemainPropNumber;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<UObject*,bool> PropPointsMap;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<UObject*,APeachProp*> PonitToPropMap;

	
	UFUNCTION(BlueprintCallable)
	void BeginTimerToSpawnProp();
	
	UFUNCTION()
	void SpawnProp();

	UFUNCTION()
	void ResetPiontMap(APeachProp* PeachProp);

	FTimerHandle TimerHandle;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	TSubclassOf<APeachProp> BananaClass;
	TSubclassOf<APeachProp> AppleClass;
	TSubclassOf<APeachProp> WatermelonClass;
	TSubclassOf<APeachProp> OrangeClass;
	TSubclassOf<APeachProp> DurianClass; 
;
};
