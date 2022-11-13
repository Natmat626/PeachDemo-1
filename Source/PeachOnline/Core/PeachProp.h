// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PeachProp.generated.h"
UENUM()
enum class PropClass
{
	Banana =0,
	Apple = 1,
	Watermelon =2,
	Orange = 3,
	Durian =4,
};
UCLASS()
class PEACHONLINE_API APeachProp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APeachProp();
#pragma region Component
	
	UPROPERTY(Category=Character,VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"));
	USphereComponent* SphereCollisionComp ;
	
	UPROPERTY(Category=Character,VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"));
	UStaticMeshComponent* StaticMesh;

	FTimerHandle TimerHandle;
	UPROPERTY(EditAnywhere,Replicated,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"))
	PropClass PropClass;

	/*
	UFUNCTION(Server,Reliable,WithValidation)
	void ServerOnPropHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void ServerOnPropHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	bool ServerOnPropHit_Validate(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	*/

	UFUNCTION(Server,Reliable,WithValidation)
	void ServerOnPropOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	void ServerOnPropOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool ServerOnPropOverlap_Validate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma  endregion 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
