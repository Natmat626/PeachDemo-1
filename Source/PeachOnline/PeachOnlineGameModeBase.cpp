// Copyright Epic Games, Inc. All Rights Reserved.


#include "PeachOnlineGameModeBase.h"

#include "Core/BaseCharacter.h"
#include "Kismet/BlueprintMapLibrary.h"
#include "Kismet/KismetMathLibrary.h"
PRAGMA_DISABLE_OPTIMIZATION

void APeachOnlineGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	BananaClass = LoadClass<APeachProp>(nullptr,TEXT("Blueprint'/Game/Prop/BP_Banana.BP_Banana_C'"));
	AppleClass = LoadClass<APeachProp>(nullptr,TEXT("Blueprint'/Game/Prop/BP_Apple.BP_Apple_C'"));
	WatermelonClass = LoadClass<APeachProp>(nullptr,TEXT("Blueprint'/Game/Prop/BP_Watermelon.BP_Watermelon_C'"));
	OrangeClass = LoadClass<APeachProp>(nullptr,TEXT("Blueprint'/Game/Prop/BP_Orange.BP_Orange_C'"));
	DurianClass = LoadClass<APeachProp>(nullptr,TEXT("Blueprint'/Game/Prop/BP_Durian.BP_Durian_C'"));
}

APlayerController* APeachOnlineGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal,
	const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	auto it = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	auto its = Cast<APeachPlayerController>(it);
	if(PlayerLoginUI!=nullptr)
	{
		its->PlayerName = PlayerLoginUI->PlayerName->GetText().ToString();
	}
	
	return its;
}


void APeachOnlineGameModeBase::BeginTimerToSpawnProp()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APeachOnlineGameModeBase::SpawnProp, 0.2f,true);
}

void APeachOnlineGameModeBase::SpawnProp()
{
	if(RemainPropNumber>0)
	{
		auto TempPoint = PropPonits[UKismetMathLibrary::RandomInteger(MaxPropPointsIndex)];
		if( *PropPointsMap.Find(TempPoint) == false)
		{
			auto RandomPropClass = UKismetMathLibrary::RandomInteger(MaxPropPointsIndex);
			switch (RandomPropClass)
			{
				case (0):
					{
						auto PropPtr = GetWorld()->SpawnActor<APeachProp>(BananaClass,Cast<AActor>(TempPoint)->GetActorLocation(),Cast<AActor>(TempPoint)->GetActorRotation());
						RemainPropNumber--;
						PropPointsMap.Add(TempPoint,true);
						PonitToPropMap.Add(TempPoint,PropPtr);
						break;
					}
			case (1):
					{
						auto PropPtr = GetWorld()->SpawnActor<APeachProp>(AppleClass,Cast<AActor>(TempPoint)->GetActorLocation(),Cast<AActor>(TempPoint)->GetActorRotation());
						RemainPropNumber--;
						PropPointsMap.Add(TempPoint,true);
						PonitToPropMap.Add(TempPoint,PropPtr);
						break;
					}
			case (2):
					{
						auto PropPtr = GetWorld()->SpawnActor<APeachProp>(WatermelonClass,Cast<AActor>(TempPoint)->GetActorLocation(),Cast<AActor>(TempPoint)->GetActorRotation());
						RemainPropNumber--;
						PropPointsMap.Add(TempPoint,true);
						PonitToPropMap.Add(TempPoint,PropPtr);
						break;
					}
			case (3):
					{
						auto PropPtr = GetWorld()->SpawnActor<APeachProp>(OrangeClass,Cast<AActor>(TempPoint)->GetActorLocation(),Cast<AActor>(TempPoint)->GetActorRotation());
						RemainPropNumber--;
						PropPointsMap.Add(TempPoint,true);
						PonitToPropMap.Add(TempPoint,PropPtr);
						break;
					}
			case (4):
					{
						auto PropPtr = GetWorld()->SpawnActor<APeachProp>(DurianClass,Cast<AActor>(TempPoint)->GetActorLocation(),Cast<AActor>(TempPoint)->GetActorRotation());
						RemainPropNumber--;
						PropPointsMap.Add(TempPoint,true);
						PonitToPropMap.Add(TempPoint,PropPtr);
						break;
					}
			}
		}
		else
		{
			return;
		}
	}
}

void APeachOnlineGameModeBase::ResetPiontMap(APeachProp* PeachProp)
{
	
	for(int i=0;i<PropPonits.Num();i++)
	{
		if(PeachProp == *PonitToPropMap.Find(PropPonits[i]))
		{
			PonitToPropMap.Add(PropPonits[i],nullptr);
			return;
		} 
	}
	
	//auto it = PonitToPropMap.GetKeys()
}



