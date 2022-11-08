// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PeachPlayerController.h"
#include "PeachPortal.h"
#include "ProjectilePeach.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "BaseCharacter.generated.h"
UENUM()
enum class WalkState
{
	Walk =0,
	Run = 1
};
UCLASS()
class PEACHONLINE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	// Sets default values for this character's properties
	ABaseCharacter();
private:
#pragma region Component
	UPROPERTY(Category=Character,VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess = "true"));
	UCameraComponent* PlayerCamera;

	UPROPERTY(Category=Character,VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"));
	UCameraComponent* PlayerCameraBack;
	
	UPROPERTY(Category=Character,BlueprintReadOnly,meta=(AllowPrivateAccess = "true"));
	UAnimInstance* CLientArmsAnimBP;

	UPROPERTY(Category=Character,BlueprintReadOnly,meta=(AllowPrivateAccess = "true"));
	UAnimInstance* ServerBodyAnimBP;

	UPROPERTY(Category=Character,VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess = "true"));
	USpringArmComponent* CameraSpringArm;
	
	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess = "true"))
	APeachPlayerController* FPSPlayerController;

	UFUNCTION()
	void DelayBeginPlayCallBack();
#pragma endregion

#pragma region Input
	
	void MoveRight(float AxisValue);
	void MoveForward(float AxisValue);
	
	void JumpAction();
	void StopJumpAction();
	void HighSpeedRunAction();
	void NormalSpeedWalkAction();
	void FireFart();
	void LookBack();
	void StopLookBack();
	void ResetProtal();
	void CallBackPortal();



#pragma endregion 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
# define MaxRunEnergy 100;

	
	UPROPERTY(BlueprintReadOnly,Replicated)
	float RunEnergy;
	
	UPROPERTY(BlueprintReadOnly,Replicated)
	WalkState PlayerWalkState;

	UPROPERTY(BlueprintReadOnly,Replicated)
	bool IsSetPortal;

	UPROPERTY(BlueprintReadOnly,Replicated)
	bool IsAiming;

	UPROPERTY(BlueprintReadOnly,Replicated)
	bool HavePlacedProtal;

	UPROPERTY(BlueprintReadOnly,Replicated)
	APeachPortal* PtrPortal;
	
	UPROPERTY(BlueprintReadOnly,Replicated)
	bool CanFire;
	// Called every frame

	FTimerHandle TimerHandle;
	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	void RefreshRunEnergy(float DeltaTime);

	void ResetFireState();

	void PortalFunction();

	
   
	void PutPortalLineTeace(FVector CameraLocation, FRotator CameraRotation);
#pragma region Networking
	
	UFUNCTION(Server,Reliable,WithValidation)
	void ServerHighSpeedRunAction();
	void ServerHighSpeedRunAction_Implementation();
	bool ServerHighSpeedRunAction_Validate();

	UFUNCTION(Server,Reliable,WithValidation)
	void ServerNormalSpeedWalkAction();
	void ServerNormalSpeedWalkAction_Implementation();
	bool ServerNormalSpeedWalkAction_Validate();
	
	UFUNCTION(Server,Reliable,WithValidation)
	void ServerFireFart();
	void ServerFireFart_Implementation();
	bool ServerFireFart_Validate();

	UFUNCTION(Server,Reliable,WithValidation)
	void ServerSetProtal();
	void ServerSetProtal_Implementation();
	bool ServerSetProtal_Validate();

	UFUNCTION(Server,Reliable,WithValidation)
	void ServerSetIsAiming(bool Newstate);
	void ServerSetIsAiming_Implementation(bool Newstate);
	bool ServerSetIsAiming_Validate(bool Newstate);

	UFUNCTION(Server,Reliable,WithValidation)
	void ServerCallBackPortal();
	void ServerCallBackPortal_Implementation();
	bool ServerCallBackPortal_Validate();

	UFUNCTION(Server,Reliable,WithValidation)
	void ServerResetState();
	void ServerResetState_Implementation();
	bool ServerResetState_Validate();

	UFUNCTION(Server,Reliable,WithValidation)
	void ServerPortalFunction();
	void ServerPortalFunction_Implementation();
	bool ServerPortalFunction_Validate();

#pragma  endregion
protected:
	TSubclassOf<AProjectilePeach> ProjectileClass;
	TSubclassOf<APeachPortal>  PortalClass;
};
