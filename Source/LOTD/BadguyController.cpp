// Fill out your copyright notice in the Description page of Project Settings.


#include "BadguyController.h"
#include "Badguy.h"
#include "CowboyCharacter.h"
#include "Kismet/GameplayStatics.h"

ABadguyController::ABadguyController()
{
    // Enable Tick for this controller
    PrimaryActorTick.bCanEverTick = true;
}

void ABadguyController::BeginPlay()
{
    Super::BeginPlay();

    cb = Cast<ACowboyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void ABadguyController::OnPossess(APawn* InPawn)
{
    //Super::Possess(InPawn);
    //UE_LOG(LogTemp, Warning, TEXT("ABadguyController has possessed: %s"), *InPawn->GetName());
    
    guy = Cast<ABadguy>(InPawn);
}

void ABadguyController::OnUnPossess()
{
    Super::UnPossess();
}

void ABadguyController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!inPath)
    {
        MoveToLocation(cb->GetActorLocation(), guy->DesiredShootRange, true, true, true, guy->CanStrafeWhileRunning);
    }
    
}

void ABadguyController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    inPath = false;
}