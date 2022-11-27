// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalPutUIActor.h"

// Sets default values
APortalPutUIActor::APortalPutUIActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent -> SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APortalPutUIActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void APortalPutUIActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

