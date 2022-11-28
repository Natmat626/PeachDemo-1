// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KillerNotice.h"
#include "PeachPlayerController.h"
#include "PeachPortal.h"
#include "PortalPutUIActor.h"
#include "ProjectilePeach.h"
#include "Camera/CameraComponent.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseCharacter.generated.h"
UENUM()
enum class WalkState
{
	Walk =0,
	Run = 1
};

USTRUCT(BlueprintType)
struct FDatas:public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FDatas() 
	:PropertyName(TEXT(""))
	,Value(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="FDatas")
	FString PropertyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FDatas")
	float Value;
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
	
	UPROPERTY(BlueprintReadOnly,Replicated)
    int BananaCount;
    
    UPROPERTY(BlueprintReadOnly,Replicated)
    int AppleCount;

	UPROPERTY(BlueprintReadOnly,Replicated)
	int WatermelonCount;

	UPROPERTY(BlueprintReadOnly,Replicated)
	int OrangeCount;

	UPROPERTY(BlueprintReadOnly,Replicated)
	int DurianCount;


	UPROPERTY(BlueprintReadOnly,Replicated)
	APeachPlayerController* Killerptr;
	// Called every frame

	FTimerHandle TimerHandle;
	FTimerHandle TimerHandle2;
	
	virtual void Tick(float DeltaTime) override;

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	void RefreshRunEnergy(float DeltaTime);

	void ResetFireState();

	void PortalFunction();

	void SetPortalVisableState();
   
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

	UFUNCTION(Server,Reliable,WithValidation)
	void ServerSetMoveState(int State);
	void ServerSetMoveState_Implementation(int State);
	bool ServerSetMoveState_Validate(int State);

	UFUNCTION(Server,Reliable,WithValidation)
	void ServerAskForKillNotice();
	void ServerAskForKillNotice_Implementation();
	bool ServerAskForKillNotice_Validate();

	UFUNCTION(NetMulticast,Reliable,WithValidation)
	void ServerSetPortalVisable(APeachPortal* Portal);
	void ServerSetPortalVisable_Implementation(APeachPortal* Portal);
	bool ServerSetPortalVisable_Validate(APeachPortal* Portal);

	UFUNCTION(NetMulticast,Reliable,WithValidation)
	void ServerShowKillerNotice(const FString&  Killer, const FString&  Bekillered);
	void ServerShowKillerNotice_Implementation( const FString&   Killer, const FString&   Bekillered);
	bool ServerShowKillerNotice_Validate(const FString&    Killer, const FString&    Bekillered);
#pragma  endregion
protected:
	TSubclassOf<AProjectilePeach> ProjectileClass;
	TSubclassOf<APeachPortal>  PortalClass;
	TSubclassOf<APortalPutUIActor>  PortalUICLass;
	TSubclassOf<UKillerNotice> KillerNoticeClassUnit;
	APortalPutUIActor* PortalPutUIActorPtr;
	TWeakPtr<APortalPutUIActor> test;

	FVector PortalUIEndLocation;
	FHitResult PortalUIHitResult;
	FVector PortalUICameraForwardVector ;
	TArray<AActor*> PortalUIIgnoreArray;
	float TableRunspeed;
	UDataTable* Table;
};
