// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include <iso646.h>

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "PeachOnline/PeachOnlineGameModeBase.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileClass = LoadClass<AProjectilePeach>(nullptr,TEXT("Blueprint'/Game/Fart/BP_Fart.BP_Fart_C'"));
	PortalClass = LoadClass<APeachPortal>(nullptr,TEXT("Blueprint'/Game/Portal/BP_Portal.BP_Portal_C'"));
#pragma region Component
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if(CameraSpringArm)
	{
		CameraSpringArm->SetupAttachment(RootComponent);
	}
	PlayerCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	if(PlayerCamera)
	{
		PlayerCamera->SetupAttachment(CameraSpringArm);
		PlayerCamera->bUsePawnControlRotation = false;
	}
	PlayerCameraBack = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCameraBack"));
	if(PlayerCameraBack)
	{
		//PlayerCameraBack->SetupAttachment(Mesh);
		PlayerCameraBack->SetupAttachment(RootComponent);
		PlayerCameraBack->bUsePawnControlRotation = false;
	}
	/*FPSArmsmesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPSArmsmesh"));
	if(FPSArmsmesh)
	{
		FPSArmsmesh->SetupAttachment(PlayerCamera);
		FPSArmsmesh->SetOnlyOwnerSee(true);
	}
	Mesh->SetOwnerNoSee(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);*/
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetCharacterMovement()->bOrientRotationToMovement = 1;
   
	
#pragma endregion 

}

void ABaseCharacter::DelayBeginPlayCallBack()
{
	FPSPlayerController = Cast<APeachPlayerController>( GetController());
	if(FPSPlayerController)
	{
		
	}
	else
	{
		//begin delay
		FLatentActionInfo ActionInfo;
		ActionInfo.ExecutionFunction=TEXT("DelayBeginPlayCallBack");
		ActionInfo.CallbackTarget=this;
		ActionInfo.UUID=FMath::Rand();
		ActionInfo.Linkage=0;
		UKismetSystemLibrary::Delay(this,0.5,ActionInfo);
	}
}

void ABaseCharacter::MoveRight(float AxisValue)
{
	
	// find out which way is right
	const FRotator Rotation = FPSPlayerController->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// add movement in that direction
	AddMovementInput(Direction, AxisValue);
	
}

void ABaseCharacter::MoveForward(float AxisValue)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}

void ABaseCharacter::JumpAction()
{
	Jump();
}

void ABaseCharacter::StopJumpAction()
{
	StopJumping();
}




// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	IsSetPortal = false;
	HavePlacedProtal = false;
	IsAiming = false;
	CanFire = true;
	PtrPortal = nullptr;
	RunEnergy=MaxRunEnergy;
	PlayerWalkState = WalkState::Walk;
	
	BananaCount = 0;
	AppleCount = 0;
	WatermelonCount = 0;
	OrangeCount = 0;
	DurianCount = 0;
	FPSPlayerController = Cast<APeachPlayerController>( GetController());
	if(FPSPlayerController)
	{
		
	}
	else
	{
		//begin delay
		FLatentActionInfo ActionInfo;
		ActionInfo.ExecutionFunction=TEXT("DelayBeginPlayCallBack");
		ActionInfo.CallbackTarget=this;
		ActionInfo.UUID=FMath::Rand();
		ActionInfo.Linkage=0;
		UKismetSystemLibrary::Delay(this,0.5,ActionInfo);
	}
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RefreshRunEnergy(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis(TEXT("MoveRight"),this,&ABaseCharacter::MoveRight);
	InputComponent->BindAxis(TEXT("MoveForward"),this,&ABaseCharacter::MoveForward);

	InputComponent->BindAxis(TEXT("Turn"),this,&ABaseCharacter::AddControllerYawInput);
	InputComponent->BindAxis(TEXT("LookUp"),this,&ABaseCharacter::AddControllerPitchInput);
	
	InputComponent->BindAction(TEXT("Run"),IE_Pressed,this,&ABaseCharacter::HighSpeedRunAction);
	InputComponent->BindAction(TEXT("Run"),IE_Released,this,&ABaseCharacter::NormalSpeedWalkAction);

	InputComponent->BindAction(TEXT("Jump"),IE_Pressed,this,&ABaseCharacter::JumpAction);
	InputComponent->BindAction(TEXT("Jump"),IE_Released,this,&ABaseCharacter::StopJumpAction);

	InputComponent->BindAction(TEXT("LookBack"),IE_Pressed,this,&ABaseCharacter::LookBack);
	InputComponent->BindAction(TEXT("LookBack"),IE_Released,this,&ABaseCharacter::StopLookBack);

	InputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&ABaseCharacter::FireFart);

	InputComponent->BindAction(TEXT("SetPortal"),IE_Pressed,this,&ABaseCharacter::ResetProtal);

	InputComponent->BindAction(TEXT("CallBackPortal"),IE_Pressed,this,&ABaseCharacter::CallBackPortal);
	
	InputComponent->BindAction(TEXT("PortalFunction"),IE_Pressed,this,&ABaseCharacter::PortalFunction);
}

void ABaseCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	//Super::FellOutOfWorld(dmgType);
	APeachPlayerController*  OnlinePeachPlayerController = Cast<APeachPlayerController>(FPSPlayerController);
	if(OnlinePeachPlayerController)
	{
		ServerResetState();
		OnlinePeachPlayerController->DeathMatchDeth(this);
		
	}
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ABaseCharacter,IsAiming,COND_None);
	DOREPLIFETIME_CONDITION(ABaseCharacter,PlayerWalkState,COND_None);
	DOREPLIFETIME_CONDITION(ABaseCharacter,RunEnergy,COND_None);
	DOREPLIFETIME_CONDITION(ABaseCharacter,IsSetPortal,COND_None);
	DOREPLIFETIME_CONDITION(ABaseCharacter,PtrPortal,COND_None);
	DOREPLIFETIME_CONDITION(ABaseCharacter,CanFire,COND_None);
	DOREPLIFETIME_CONDITION(ABaseCharacter,BananaCount,COND_None);
	DOREPLIFETIME_CONDITION(ABaseCharacter,AppleCount,COND_None);
	DOREPLIFETIME_CONDITION(ABaseCharacter,WatermelonCount,COND_None);
	DOREPLIFETIME_CONDITION(ABaseCharacter,OrangeCount,COND_None);
	DOREPLIFETIME_CONDITION(ABaseCharacter,DurianCount,COND_None);
}

void ABaseCharacter::RefreshRunEnergy(float DeltaTime)
{
	if(PlayerWalkState == WalkState::Walk and RunEnergy<100.f)
	{
		RunEnergy = RunEnergy + 0.1;
		return;
	}
	if(PlayerWalkState== WalkState::Run and RunEnergy>0.f)
	{
		RunEnergy = RunEnergy - 0.1;
		return;
	}
	if(RunEnergy<=0.f)
	{
		PlayerWalkState=WalkState::Walk;
		CharacterMovement->MaxWalkSpeed=300;
		ServerNormalSpeedWalkAction();
	}
}

void ABaseCharacter::ResetFireState()
{
	CanFire = true;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void ABaseCharacter::PortalFunction()
{
	ServerPortalFunction();
}

void ABaseCharacter::SetPortalVisableState()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle2);
	if(UKismetSystemLibrary::IsServer(this))
	{
		ServerSetPortalVisable(PtrPortal);
	}
}

void ABaseCharacter::ServerPortalFunction_Implementation()
{
	if(PtrPortal!=nullptr)
	{
		if(RunEnergy>=20)
		{
			FVector NewLocation  = PtrPortal->GetActorLocation() + PtrPortal->GetActorForwardVector()*40;
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = this;
			RunEnergy=RunEnergy-20;
			GetWorld()->SpawnActor<AProjectilePeach>(ProjectileClass,NewLocation,PtrPortal->GetActorRotation(),SpawnParams);
		}
	}
	
}

bool ABaseCharacter::ServerPortalFunction_Validate()
{
	return true;
}

void ABaseCharacter::ServerSetMoveState_Implementation(int State)
{
	if(State==1)
	{
		GetCharacterMovement()->bOrientRotationToMovement = 0;
		GetCharacterMovement()->bUseControllerDesiredRotation = 1;
	}
	else
	{
		GetCharacterMovement()->bOrientRotationToMovement = 0;
		GetCharacterMovement()->bUseControllerDesiredRotation = 0;
	}
	
}

bool ABaseCharacter::ServerSetMoveState_Validate(int State)
{
	return true;
}

void ABaseCharacter::ServerSetPortalVisable_Implementation(APeachPortal* Portal)
{
	if(Portal!=nullptr)
	{
		Portal->StaticMesh->SetOnlyOwnerSee(false);
	}
	
}

bool ABaseCharacter::ServerSetPortalVisable_Validate(APeachPortal* Portal)
{
	return true;
}


void ABaseCharacter::PutPortalLineTeace(FVector CameraLocation, FRotator CameraRotation)
{
	FVector EndLocation;
	FHitResult HitResult;
	FVector CameraForwardVector = UKismetMathLibrary::GetForwardVector(CameraRotation);
	TArray<AActor*> IgnoreArray;
	IgnoreArray.Add(this);

	EndLocation = CameraLocation + CameraForwardVector * 1000;//可放置的长度
	bool LineHitSuccess = UKismetSystemLibrary::LineTraceSingle(GetWorld(),CameraLocation,EndLocation,ETraceTypeQuery::TraceTypeQuery1,false,
		IgnoreArray,EDrawDebugTrace::None,HitResult,true,FLinearColor::Red
		,FLinearColor::Green,30.f);

	if(LineHitSuccess)
	{
		if(PtrPortal==nullptr)
		{
			//UKismetSystemLibrary::PrintString(GetWorld(),FString::Printf(TEXT("Name :%s "),*HitResult.Normal.ToString()));
			FRotator XRotator = UKismetMathLibrary::MakeRotFromX(HitResult.Normal);
			FVector LocationNew = FVector(HitResult.Location.X +HitResult.Normal.X,HitResult.Location.Y +HitResult.Normal.Y,HitResult.Location.Z +HitResult.Normal.Z);

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = this;
			//SpawnParams.Instigator = GetInstigator();
			
			PtrPortal = GetWorld()->SpawnActor<APeachPortal>(PortalClass,LocationNew,XRotator,SpawnParams);
			if(OrangeCount>=1)//有橘子，传送门隐身10s
			{
				PtrPortal->CanTransmit=DurianCount;
				PtrPortal->CanOtherNotSee=OrangeCount;
				DurianCount=0;
				OrangeCount=0;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &ABaseCharacter::SetPortalVisableState, 10.0f, false);
			}
			else if(OrangeCount==0)//没有橘子，传送门不隐身
			{
				PtrPortal->CanTransmit=DurianCount;
				PtrPortal->CanOtherNotSee=OrangeCount;
				DurianCount=0;
				OrangeCount=0;
				//PtrPortal = Cast<APeachPortal>(UGameplayStatics::BeginSpawningActorFromClass(this,PortalClass,FTransform(XRotator,LocationNew,FVector(1,1,1)),ESpawnActorCollisionHandlingMethod::Undefined,this));
				//PtrPortal->InitCanOtherSee(true);
				//UGameplayStatics::FinishSpawningActor(PtrPortal, FTransform(XRotator,LocationNew,FVector(1,1,1)));
				GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &ABaseCharacter::SetPortalVisableState, 0.1f, false);
			}
			IsSetPortal = false;
		}
		
		
	}
	
}

void ABaseCharacter::ServerHighSpeedRunAction_Implementation()
{
	CharacterMovement->MaxWalkSpeed=600;
	PlayerWalkState = WalkState::Run;
	
}

bool ABaseCharacter::ServerHighSpeedRunAction_Validate()
{
	return  true;
}

void ABaseCharacter::ServerNormalSpeedWalkAction_Implementation()
{
	CharacterMovement->MaxWalkSpeed=300;
	PlayerWalkState = WalkState::Walk;
}

bool ABaseCharacter::ServerNormalSpeedWalkAction_Validate()
{
	return true;
}

void ABaseCharacter::ServerFireFart_Implementation()
{
	
	if(IsAiming == true)
	{
		if(CanFire)
		{
			//不是放置传送门状态下放屁
			//FActorSpawnParameters SpawnParameters;
			//SpawnParameters.Owner = this;
			if(RunEnergy>=20)
			{
				FVector NewLocation  = PlayerCameraBack->GetComponentLocation() + PlayerCameraBack->GetForwardVector()*40;
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = this;
				RunEnergy=RunEnergy-20;
				GetWorld()->SpawnActor<AProjectilePeach>(ProjectileClass,NewLocation,PlayerCameraBack->GetComponentRotation(),SpawnParams);
				CanFire = false;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseCharacter::ResetFireState, 0.2f, false);
				return;
			}
			else
			{
				return;
			}
			
		}
			
		
	}
	else if(IsSetPortal == true)
	{
		PutPortalLineTeace(PlayerCamera->GetComponentLocation(),PlayerCamera->GetComponentRotation());
		
		//放置传送门状态
		return;
	}
}

bool ABaseCharacter::ServerFireFart_Validate()
{
	return true;
}

void ABaseCharacter::ServerSetProtal_Implementation()
{
	if(PtrPortal!=nullptr)
	{
		if(PtrPortal->CanTransmit==1)//只有这种情况下才能传送
		{
			FVector NewLocation = FVector(PtrPortal->GetActorLocation().X+PtrPortal->GetActorForwardVector().X*10,
			PtrPortal->GetActorLocation().Y+PtrPortal->GetActorForwardVector().Y*10,
			PtrPortal->GetActorLocation().Z+PtrPortal->GetActorForwardVector().Z*10+50);
			this->SetActorLocation(NewLocation);
			PtrPortal->CanTransmit=0;
			return;
		}
		else
		{
			IsSetPortal = false;
		}
		//传送
	}
	//还没有传送门
	if(IsSetPortal == true)
	{
		IsSetPortal = false;
		return;
	}
	else if(IsSetPortal == false)
	{
		IsSetPortal = true;
	}
}

void ABaseCharacter::ServerSetIsAiming_Implementation(bool Newstate)
{
	IsAiming = Newstate;
}

bool ABaseCharacter::ServerSetIsAiming_Validate(bool Newstate)
{
	return true;
}

void ABaseCharacter::ServerCallBackPortal_Implementation()
{
	if(PtrPortal == nullptr)
	{
		return;
	}
	if(PtrPortal !=nullptr)
	{
		PtrPortal->Destroy();
		PtrPortal =nullptr;
	}
}

bool ABaseCharacter::ServerCallBackPortal_Validate()
{
	return true;
}

void ABaseCharacter::ServerResetState_Implementation()
{
	if(PtrPortal!=nullptr)
	{
		PtrPortal->Destroy();
	}
	PtrPortal = nullptr;
	Cast<APeachOnlineGameModeBase>(GetWorld()->GetAuthGameMode())->RemainPropNumber=Cast<APeachOnlineGameModeBase>(GetWorld()->GetAuthGameMode())->RemainPropNumber
	+BananaCount+AppleCount+WatermelonCount+OrangeCount+DurianCount;
}

bool ABaseCharacter::ServerResetState_Validate()
{
	return true;
}


bool ABaseCharacter::ServerSetProtal_Validate()
{
	return true;
}


void ABaseCharacter::HighSpeedRunAction()
{
	if(RunEnergy>0)
	{
		PlayerWalkState = WalkState::Run;
		CharacterMovement->MaxWalkSpeed=600;
		ServerHighSpeedRunAction();
	}
	else
	{
		PlayerWalkState = WalkState::Walk;
	}
	
}

void ABaseCharacter::NormalSpeedWalkAction()
{
	PlayerWalkState = WalkState::Walk;
	CharacterMovement->MaxWalkSpeed=300;
	ServerNormalSpeedWalkAction();
}

void ABaseCharacter::FireFart()
{
	
	//GetWorld()->SpawnActor<AProjectilePeach>(ProjectileClass,PlayerCamera->GetComponentLocation(),PlayerCamera->GetComponentRotation());
	ServerFireFart();
}

void ABaseCharacter::LookBack()
{
	if(IsSetPortal == true)
	{
		return;
	}
	ServerSetIsAiming(true);
	PlayerCamera->SetActive(false,false);
	PlayerCameraBack->SetActive(true,true);


	GetCharacterMovement()->bOrientRotationToMovement = 0;
	GetCharacterMovement()->bUseControllerDesiredRotation = 1;
	ServerSetMoveState(1);
}

void ABaseCharacter::StopLookBack()
{
	ServerSetIsAiming(false);
	PlayerCamera->SetActive(true,true);
	PlayerCameraBack->SetActive(false,false);
	GetCharacterMovement()->bOrientRotationToMovement = 0;
	GetCharacterMovement()->bUseControllerDesiredRotation = 0;
	ServerSetMoveState(0);
}

void ABaseCharacter::ResetProtal()
{
	ServerSetProtal();
}

void ABaseCharacter::CallBackPortal()
{
	ServerCallBackPortal();
} 


