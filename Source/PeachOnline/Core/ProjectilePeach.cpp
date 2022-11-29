// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilePeach.h"

#include "BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

PRAGMA_DISABLE_OPTIMIZATION
// Sets default values
AProjectilePeach::AProjectilePeach()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileFart = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileFart"));
	ProjectileFart->SetIsReplicated(true);
	SphereCollisionComp  = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComp"));
	RootComponent = SphereCollisionComp;

	/*StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);*/
	//SphereCollisionComp->OnComponentHit.AddDynamic(this,&AProjectilePeach::ServerOnFartHit);
	SphereCollisionComp->IgnoreActorWhenMoving(GetOwner(),true);
	SphereCollisionComp->OnComponentBeginOverlap.AddDynamic(this,&AProjectilePeach::ServerOnPropOverlap);
	ProjectileFart->InitialSpeed = 0;
	ProjectileFart->MaxSpeed = 8000;
	//ProjectileFart->SetUpdatedComponent(RootComponent);
	Table = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/DesignerTable/DesignerTable.DesignerTable'"));
}

// Called when the game starts or when spawned
void AProjectilePeach::BeginPlay()
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
			if(pRow->PropertyName==TEXT("TablePeachExistTime"))
			{
				TablePeachExistTime=pRow->Value;
				continue;
			}
			else if(pRow->PropertyName==TEXT("TablePeachSpeed"))
			{
				TablePeachSpeed=pRow->Value;
				continue;
			}
			else if(pRow->PropertyName==TEXT("TablePeachHitPlayerSpeed"))
			{
				TablePeachHitPlayerSpeed=pRow->Value;
				continue;
			}
			else if(pRow->PropertyName==TEXT("TablePeachExistTimeAdd"))
			{
				TablePeachExistTimeAdd=pRow->Value;
				continue;
			}
			else if(pRow->PropertyName==TEXT("TablePeachSpeedAdd"))
			{
				TablePeachSpeedAdd=pRow->Value;
				continue;
			}
			else if(pRow->PropertyName==TEXT("TablePeachHitPlayerSpeedAdd"))
			{
				TablePeachHitPlayerSpeedAdd=pRow->Value;
				continue;
			}
		}
	}
	
	if(UKismetSystemLibrary::IsServer(this))
	{
		auto Ownerptr = Cast<ABaseCharacter>(GetOwner());
		InitFartSpeed(Ownerptr->BananaCount);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectilePeach::DestroyFartOnTime, TablePeachExistTime+TablePeachExistTimeAdd*Ownerptr->WatermelonCount, false);
	}
	
	
	
}

// Called every frame
void AProjectilePeach::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void AProjectilePeach::DestroyFartOnTime()
{
	ServerDestroyFartOnTime();
}

void AProjectilePeach::InitFartSpeed(int Number)
{
	ProjectileFart->SetVelocityInLocalSpace(FVector(1,0,0)*(TablePeachSpeed+TablePeachSpeedAdd*Number));
	//ProjectileFart->InitialSpeed = 1000*Number;
	//ProjectileFart->MaxSpeed = 1000*Number;
	//ProjectileFart->SetAutoActivate(1);
	//ServerInitFartSpeed();
}

void AProjectilePeach::ServerInitFartSpeed_Implementation()
{
	ProjectileFart->InitialSpeed = 1000;
	ProjectileFart->MaxSpeed =1000;
}

bool AProjectilePeach::ServerInitFartSpeed_Validate()
{
	return true;
}


void AProjectilePeach::ServerOnFartHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(UKismetSystemLibrary::IsServer(this))
	{
		
		if(Cast<ABaseCharacter>(Hit.Actor)!=nullptr)
		{
			auto itsss = Cast<ABaseCharacter>(Hit.Actor);
			auto itssss = Cast<ABaseCharacter>(GetOwner());
			if(itsss == itssss)
			{
				return;
			}
			auto AppleNumber = Cast<ABaseCharacter>(GetOwner())->AppleCount;
			FHitResult OutSweepHitResult;
			//Cast<ABaseCharacter>(Hit.Actor)->AddActorWorldOffset(Hit.Normal*-1*3000,true,&OutSweepHitResult,ETeleportType::None);
			
			//Cast<ABaseCharacter>(Hit.Actor)->LaunchCharacter(Hit.Normal*-1*(3000+AppleNumber*300),false,false);//移动 不能模拟物理
			auto it =this->GetActorForwardVector();
			it.Normalize();
			FVector its = FVector(it.X,it.Y,it.Z);
			Cast<ABaseCharacter>(Hit.Actor)->LaunchCharacter(its*(TablePeachHitPlayerSpeed+AppleNumber*TablePeachHitPlayerSpeedAdd),false,false);//移动 不能模拟物理
		
			this->Destroy();
			return;
		}
		this->Destroy();
		//UKismetSystemLibrary::PrintString(GetWorld(),FString::Printf(TEXT("Name :%s "),*OtherActor->GetName()));
		//UKismetSystemLibrary::PrintString(GetWorld(),FString::Printf(TEXT("Name :%s "),*Hit.Normal.ToString()));
	}
	else
	{
	}
	
}

bool AProjectilePeach::ServerOnFartHit_Validate(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	return true;
}

void AProjectilePeach::ServerOnPropOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UKismetSystemLibrary::IsServer(this))
	{
		if(Cast<AProjectilePeach>(SweepResult.Actor) == this)
		{
			return;
		}
		
		if((Cast<ABaseCharacter>(GetOwner())->PtrPortal)!=nullptr)
		{
			if(Cast<APeachPortal>(SweepResult.Actor) == (Cast<ABaseCharacter>(GetOwner())->PtrPortal))
			{
				return;
			}
		}
		
		if(Cast<ABaseCharacter>(SweepResult.Actor)!=nullptr)
		{
			
			if(Cast<ABaseCharacter>(SweepResult.Actor) == Cast<ABaseCharacter>(GetOwner()))
			{
				return;
			}
			auto AppleNumber = Cast<ABaseCharacter>(GetOwner())->AppleCount;
			FHitResult OutSweepHitResult;
			//Cast<ABaseCharacter>(Hit.Actor)->AddActorWorldOffset(Hit.Normal*-1*3000,true,&OutSweepHitResult,ETeleportType::None);
			
			//Cast<ABaseCharacter>(Hit.Actor)->LaunchCharacter(Hit.Normal*-1*(3000+AppleNumber*300),false,false);//移动 不能模拟物理
			auto it =this->GetActorForwardVector();
			it.Normalize();
			FVector its = FVector(it.X,it.Y,it.Z);
			Cast<ABaseCharacter>(SweepResult.Actor)->LaunchCharacter(its*(TablePeachHitPlayerSpeed+AppleNumber*TablePeachHitPlayerSpeedAdd),false,false);//移动 不能模拟物理
			auto ItsOwner = Cast<ABaseCharacter>(this->GetOwner());
			Cast<ABaseCharacter>(SweepResult.Actor)->Killerptr = Cast<APeachPlayerController>(ItsOwner->GetController());
			this->Destroy();
			return;
		}
		this->Destroy();
		//UKismetSystemLibrary::PrintString(GetWorld(),FString::Printf(TEXT("Name :%s "),*OtherActor->GetName()));
		//UKismetSystemLibrary::PrintString(GetWorld(),FString::Printf(TEXT("Name :%s "),*Hit.Normal.ToString()));
	}
	else
	{
	}
}

bool AProjectilePeach::ServerOnPropOverlap_Validate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	return true;
}

void AProjectilePeach::ServerDestroyFartOnTime_Implementation()
{
	this->Destroy();
}

bool AProjectilePeach::ServerDestroyFartOnTime_Validate()
{
	return true;
}


