// Fill out your copyright notice in the Description page of Project Settings.


#include "PeachProp.h"

#include "BaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "PeachOnline/PeachOnlineGameModeBase.h"

// Sets default values
APeachProp::APeachProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereCollisionComp  = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComp"));
	RootComponent = SphereCollisionComp;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	//SphereCollisionComp->OnComponentHit.AddDynamic(this,&APeachProp::ServerOnPropHit);
	SphereCollisionComp->OnComponentBeginOverlap.AddDynamic(this,&APeachProp::ServerOnPropOverlap);

}

/*void APeachProp::ServerOnPropHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(UKismetSystemLibrary::IsServer(this))
	{
		auto it = Cast<ABaseCharacter>(Hit.Actor);
		if(it!=nullptr)
		{
			switch (PropClass)
			{
			case (PropClass::Banana):
				{
					it->BananaCount++;
					this->Destroy();
					break;
				}
			case (PropClass::Apple):
				{
					it->AppleCount++;
					this->Destroy();
					break;
				}
			case (PropClass::Watermelon):
				{
					it->WatermelonCount++;
					this->Destroy();
					break;
				}
			case (PropClass::Orange):
				{
					it->OrangeCount++;
					this->Destroy();
					break;
				}
			case (PropClass::Durian):
				{
					it->DurianCount++;
					this->Destroy();
					break;
				}
			}
		}
	}
}

bool APeachProp::ServerOnPropHit_Validate(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	return true;
}*/

void APeachProp::ServerOnPropOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UKismetSystemLibrary::IsServer(this))
	{
		auto it = Cast<ABaseCharacter>(OtherActor);
		if(it!=nullptr)
		{
			switch (PropClass)
			{
			case (PropClass::Banana):
				{
					if(it->BananaCount>=4)
					{
						return;
					}
					it->BananaCount++;
					Cast<APeachOnlineGameModeBase>(GetWorld()->GetAuthGameMode())->ResetPiontMap(this);
					this->Destroy();
					break;
				}
			case (PropClass::Apple):
				{
					if(it->AppleCount>=4)
					{
						return;
					}
					it->AppleCount++;
					Cast<APeachOnlineGameModeBase>(GetWorld()->GetAuthGameMode())->ResetPiontMap(this);
					this->Destroy();
					break;
				}
			case (PropClass::Watermelon):
				{
					if(it->WatermelonCount>=4)
					{
						return;
					}
					it->WatermelonCount++;
					Cast<APeachOnlineGameModeBase>(GetWorld()->GetAuthGameMode())->ResetPiontMap(this);
					this->Destroy();
					break;
				}
			case (PropClass::Orange):
				{
					if(it->OrangeCount>=1)
					{
						return;
					}
					it->OrangeCount++;
					Cast<APeachOnlineGameModeBase>(GetWorld()->GetAuthGameMode())->ResetPiontMap(this);
					this->Destroy();
					break;
				}
			case (PropClass::Durian):
				{
					if(it->DurianCount>=1)
					{
						return;
					}
					it->DurianCount++;
					Cast<APeachOnlineGameModeBase>(GetWorld()->GetAuthGameMode())->ResetPiontMap(this);
					this->Destroy();
					break;
				}
			}
		}
	}
}

bool APeachProp::ServerOnPropOverlap_Validate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	return true;
}

// Called when the game starts or when spawned
void APeachProp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APeachProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
void APeachProp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(APeachProp,PropClass,COND_None);

}
