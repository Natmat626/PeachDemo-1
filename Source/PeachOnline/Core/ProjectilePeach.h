// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectilePeach.generated.h"

UCLASS()
class PEACHONLINE_API AProjectilePeach : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectilePeach();

#pragma region Component

	UPROPERTY(Category=Character,VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"));
	UProjectileMovementComponent* ProjectileFart;


	UPROPERTY(Category=Character,VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"));
	USphereComponent* SphereCollisionComp ;
	
	/*UPROPERTY(Category=Character,VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"));
	UStaticMeshComponent* StaticMesh;*/

	
	FTimerHandle TimerHandle;
#pragma  endregion 


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void  DestroyFartOnTime();
#pragma region Networking
	void InitFartSpeed(int Number);
	UFUNCTION(Server,Reliable,WithValidation)
	void ServerInitFartSpeed();
	void ServerInitFartSpeed_Implementation();
	bool ServerInitFartSpeed_Validate();

	UFUNCTION(Server,Reliable,WithValidation)
	void ServerOnFartHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void ServerOnFartHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	bool ServerOnFartHit_Validate(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	UFUNCTION(Server,Reliable,WithValidation)
	void ServerOnPropOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	void ServerOnPropOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool ServerOnPropOverlap_Validate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Server,Reliable,WithValidation)
	void ServerDestroyFartOnTime();
	void ServerDestroyFartOnTime_Implementation();
	bool ServerDestroyFartOnTime_Validate();

#pragma endregion 
	
};



