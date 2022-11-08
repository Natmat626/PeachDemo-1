// Fill out your copyright notice in the Description page of Project Settings.


#include "PeachPortal.h"

// Sets default values
APeachPortal::APeachPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DetectBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectBox"));
	DetectBox->SetupAttachment(RootComponent);
	DetectBox->OnComponentBeginOverlap.AddDynamic(this,&APeachPortal::OnDetectBoxOverlapBegin);
	DetectBox->OnComponentEndOverlap.AddDynamic(this,&APeachPortal::OnDetectBoxOverlapeEnd);
	
}

void APeachPortal::OnDetectBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
}

void APeachPortal::OnDetectBoxOverlapeEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

// Called when the game starts or when spawned
void APeachPortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APeachPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

