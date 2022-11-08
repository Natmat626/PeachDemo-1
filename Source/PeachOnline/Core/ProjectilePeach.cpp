// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilePeach.h"

#include "BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AProjectilePeach::AProjectilePeach()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileFart = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileFart"));
	SphereCollisionComp  = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComp"));
	RootComponent = SphereCollisionComp;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	SphereCollisionComp->OnComponentHit.AddDynamic(this,&AProjectilePeach::ServerOnFartHit);
	SphereCollisionComp->IgnoreActorWhenMoving(GetOwner(),true);

	InitFartSpeed();

	
	//ProjectileFart->SetUpdatedComponent(RootComponent);
}

// Called when the game starts or when spawned
void AProjectilePeach::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectilePeach::DestroyFartOnTime, 0.5f, false);
	InitFartSpeed();
	
	
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

void AProjectilePeach::InitFartSpeed()
{
	ProjectileFart->InitialSpeed = 1000;
	ProjectileFart->MaxSpeed =1000;
	ServerInitFartSpeed();
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
			Cast<ABaseCharacter>(Hit.Actor)->LaunchCharacter(Hit.Normal*-1*3000,false,false);//移动 不能模拟物理
			this->Destroy();
			return;
		}
		this->Destroy();
		
		
		//UKismetSystemLibrary::PrintString(GetWorld(),FString::Printf(TEXT("Name :%s "),*OtherActor->GetName()));
		//UKismetSystemLibrary::PrintString(GetWorld(),FString::Printf(TEXT("Name :%s "),*Hit.Normal.ToString()));
	}
	else
	{
		return;
	}
	
}

bool AProjectilePeach::ServerOnFartHit_Validate(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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


