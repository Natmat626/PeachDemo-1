// Fill out your copyright notice in the Description page of Project Settings.


#include "PeachPortal.h"

#include "BaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
APeachPortal::APeachPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollisionComp  = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComp"));
	RootComponent = SphereCollisionComp;
	DetectEnermy = CreateDefaultSubobject<USphereComponent>(TEXT("DetectEnermy"));
	DetectEnermy->SetupAttachment(RootComponent);

	DetectEnermy->OnComponentBeginOverlap.AddDynamic(this,&APeachPortal::OnDetectEnermyOverlapBegin);
	DetectEnermy->OnComponentEndOverlap.AddDynamic(this,&APeachPortal::OnDetectEnermyOverlapeEnd);

	DetectCallBack = CreateDefaultSubobject<USphereComponent>(TEXT("DetectCallBack"));
	DetectCallBack->SetupAttachment(RootComponent);

	DetectCallBack->OnComponentBeginOverlap.AddDynamic(this,&APeachPortal::OnDetectCallBackOverlapBegin);
	DetectCallBack->OnComponentEndOverlap.AddDynamic(this,&APeachPortal::OnDetectCallBackOverlapeEnd);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetOnlyOwnerSee(true);

	/*DetectEnermy->SetSphereRadius(100);
	DetectCallBack->SetSphereRadius(100);*/
	Table = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/DesignerTable/DesignerTable.DesignerTable'"));
}

void APeachPortal::InitCanOtherSee(bool CanSee)
{
	StaticMesh->SetOnlyOwnerSee(CanSee);
}

void APeachPortal::OnDetectEnermyOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(Cast<ABaseCharacter>(OtherActor)==nullptr)
	{
		return;
	}
	
	if(Cast<APeachPortal>(OtherActor)!=nullptr)
	{
		if(Cast<ABaseCharacter>(OtherActor) != Cast<ABaseCharacter>( GetOwner()))
		{
			EmermyInzone++;
			return;
		}
	}
	if(Cast<ABaseCharacter>(OtherActor) != Cast<ABaseCharacter>( GetOwner()))
	{
		EmermyInzone++;
	}
}

void APeachPortal::OnDetectEnermyOverlapeEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(Cast<ABaseCharacter>(OtherActor)==nullptr)
	{
		return;
	}
	if(Cast<ABaseCharacter>(OtherActor) != Cast<ABaseCharacter>( GetOwner()))
	{
		EmermyInzone--;
	}
}

void APeachPortal::OnDetectCallBackOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(Cast<ABaseCharacter>(OtherActor)==nullptr)
	{
		return;
	}
	
	if(Cast<APeachPortal>(OtherActor)!=nullptr)
	{
		if(Cast<ABaseCharacter>(OtherActor) == Cast<ABaseCharacter>( GetOwner()))
		{
			IsCanCallBack = true;
			return;
		}
	}
	if(Cast<ABaseCharacter>(OtherActor) == Cast<ABaseCharacter>( GetOwner()))
	{
		IsCanCallBack = true;
	}
}

void APeachPortal::OnDetectCallBackOverlapeEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if(Cast<ABaseCharacter>(OtherActor)==nullptr)
	{
		return;
	}
	
	if(Cast<ABaseCharacter>(OtherActor) == Cast<ABaseCharacter>( GetOwner()))
	{
		IsCanCallBack = false;
	}
}

// Called when the game starts or when spawned
void APeachPortal::BeginPlay()
{
	Super::BeginPlay();
	if (Table != nullptr)
	{
		for (auto it : Table->GetRowMap())
		{
			FString rowName = (it.Key).ToString();
			//FProduct为你的FStruct
			FDatas* pRow = (FDatas*)it.Value;
			//输出需根据你的FStruct进行调整
			if(pRow->PropertyName==TEXT("TableDetectEnermyRadius"))
			{
				TableDetectEnermyRadius=pRow->Value;
				continue;
			}
			else if(pRow->PropertyName==TEXT("TableDetectCallBackRadius"))
			{
				TableDetectCallBackRadius=pRow->Value;
				continue;
			}
		}
	}
	DetectEnermy->SetSphereRadius(TableDetectEnermyRadius);
	DetectCallBack->SetSphereRadius(TableDetectCallBackRadius);
	
}

// Called every frame
void APeachPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APeachPortal::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(APeachPortal,CanTransmit,COND_None);
	DOREPLIFETIME_CONDITION(APeachPortal,CanOtherNotSee,COND_None);
}