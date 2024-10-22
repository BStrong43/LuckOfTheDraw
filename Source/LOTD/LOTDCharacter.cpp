// Copyright Epic Games, Inc. All Rights Reserved.

#include "LOTDCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ALOTDCharacter

ALOTDCharacter::ALOTDCharacter()
{
	RootComponent = GetCapsuleComponent();

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1500.0f, 0.0f); // ...at this rotation rate

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	CameraBoom->SetupAttachment(RootComponent);
	
	// Don't rotate the arm based on the controller
	CameraBoom->bUsePawnControlRotation = false; 
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;

	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 0.0f);
	CameraBoom->TargetArmLength = 1500.0f; // The camera follows at this distance above the character	
	CameraBoom->SetWorldLocationAndRotation(GetActorLocation(), FRotator(-90.0f, 0.0f, 0.0f)); //Camera arm rotated downwards

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Top Down Camera"));

	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	AimVector = FVector2D(0.0, CursorMaxDistance);
	Mag = CreateDefaultSubobject<UMagazine>(TEXT("Magazine"));
	Mag->FillMag(0);
}

void ALOTDCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ALOTDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	//TO DO
	//Decouple Input from pawn actions and move to custom player controller

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALOTDCharacter::Move);
																						 
		// Looking																		 
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALOTDCharacter::Look);
																						 
		//Shooting																		 
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ALOTDCharacter::Shoot);
																						 
		//Rolling																		 
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &ALOTDCharacter::Roll);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ALOTDCharacter::Move_Implementation(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		FVector ForwardDirection;
		ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ALOTDCharacter::Look_Implementation(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	LookAxisVector *= CursorSensitivity;
	FVector Loc;

	//GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, TEXT("" + LookAxisVector.ToString()));

	if (Controller != nullptr)
	{
		AimVector += LookAxisVector;
		AimVector = AimVector.GetSafeNormal() * CursorMaxDistance;

		Loc = FVector(-AimVector.Y, AimVector.X, 0.0f);
		LookAtLocation(GetActorLocation() + Loc);
	}
}

void ALOTDCharacter::Roll_Implementation()
{

}

void ALOTDCharacter::Shoot_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Shoot"));
	TSubclassOf<ABullet> Projectile = Mag->ShootChamberedBullet();

	if (Projectile)
	{
		FVector Barrel = GetActorLocation() + GetActorForwardVector() * 3;
		FRotator BulletDir = GetActorRotation();
		FActorSpawnParameters param = FActorSpawnParameters();
		param.Owner = this;
		param.Name = "Spawned Bullet";
		param.Instigator = this;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		param.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

		//If  regular Bullets get spawned, this line doesnt work properly
		GetWorld()->SpawnActor<ABullet>(Projectile, Barrel, BulletDir, param);
	}
}

void ALOTDCharacter::LookAtLocation(const FVector& TargetLocation)
{
	FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
	FRotator NewRotation = Direction.Rotation();
	SetActorRotation(NewRotation);
}