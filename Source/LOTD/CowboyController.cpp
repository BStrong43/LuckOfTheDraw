// Fill out your copyright notice in the Description page of Project Settings.


#include "CowboyController.h"
#include "CowboyCharacter.h"

ACowboyController::ACowboyController()
{
    cursorLoc = FVector(1.0, 0.0, 0.0);

    static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionFinder(TEXT("InputAction'/Game/ThirdPerson/Input/Actions/IA_Move.IA_Move'"));
    if (MoveActionFinder.Succeeded())
    {
        MoveAction = MoveActionFinder.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> LookActionFinder(TEXT("InputAction'/Game/ThirdPerson/Input/Actions/IA_Look.IA_Look'"));
    if (LookActionFinder.Succeeded())
    {
        LookAction = LookActionFinder.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> ShootActionFinder(TEXT("InputAction'/Game/ThirdPerson/Input/Actions/IA_Shoot.IA_Shoot'"));
    if (ShootActionFinder.Succeeded())
    {
        ShootAction = ShootActionFinder.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> DodgeActionFinder(TEXT("InputAction'/Game/ThirdPerson/Input/Actions/IA_Dodge.IA_Dodge'"));
    if (DodgeActionFinder.Succeeded())
    {
        DodgeAction = DodgeActionFinder.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(TEXT("InputMappingContext'/Game/ThirdPerson/Input/IMC_Default.IMC_Default'"));
    if (MappingContextFinder.Succeeded())
    {
        InputMapping = MappingContextFinder.Object;
    }
}

void ACowboyController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
    if (InputSubsystem && InputMapping)
    {
        InputSubsystem->AddMappingContext(InputMapping, 0);
    }

    //Action Bindings
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        // Bind mouse input for aiming
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACowboyController::HandleMouseLook);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACowboyController::HandleMovement);
        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ACowboyController::HandleShoot);
        EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ACowboyController::HandleDodge);
    }
}

void ACowboyController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (ACowboyCharacter* c = Cast<ACowboyCharacter>(InPawn))
    {
        cb = c;
        UE_LOG(LogTemp, Warning, TEXT("Cowboy Successfully possessed"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Cowboy not possessed"));
    }
}

void ACowboyController::HandleMovement(const FInputActionValue& Value)
{
    FVector2D InputVector = Value.Get<FVector2D>();

    //Convert to 3D vector
    FVector movement = FVector(InputVector.Y, InputVector.X, 0);

    // add movement 
    cb->AddMovementInput(movement);
}

void ACowboyController::HandleMouseLook(const FInputActionValue& Value)
{
    FVector2D MouseInput = Value.Get<FVector2D>();

    //Convert
    FVector MouseVector = FVector(-MouseInput.Y, MouseInput.X, 0);
    
    //Recalculate
    cursorLoc += (MouseVector * LookSensitivity);
    cursorLoc = cursorLoc.GetSafeNormal() * CursorDistance;

    DrawDebugPoint(GetWorld(), cb->GetActorLocation() + cursorLoc, 10.f, FColor::Red, false, 1.f);

    //Apply
    cb->Look(cursorLoc);
}

void ACowboyController::HandleDodge()
{
    cb->Dodge();
}

void ACowboyController::HandleShoot()
{
    cb->Shoot();
}