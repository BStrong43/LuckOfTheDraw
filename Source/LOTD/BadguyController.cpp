// Fill out your copyright notice in the Description page of Project Settings.


#include "BadguyController.h"
#include "Badguy.h"
#include "CowboyCharacter.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Kismet/GameplayStatics.h"

ABadguyController::ABadguyController()
{
    // Enable Tick for this controller
    PrimaryActorTick.bCanEverTick = true;

    //PathFollower = CreateDefaultSubobject<UPathFollowingComponent>(TEXT("Path Follower"));
    //SetPathFollowingComponent(PathFollower);
}

void ABadguyController::BeginPlay()
{
    Super::BeginPlay();

    cb = Cast<ACowboyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    
    NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
}

void ABadguyController::OnPossess(APawn* InPawn)
{
    SetPawn(InPawn);
    guy = Cast<ABadguy>(InPawn);
    
    if (IsValid(guy))
    {
        GetPathFollowingComponent()->SetAcceptanceRadius(guy->DesiredShootRange);
        GetPathFollowingComponent()->SetMovementComponent(guy->GetMovementComponent());
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, GetName() + FString(" Could not possess badguy"));
    }
}

void ABadguyController::OnUnPossess()
{
    
}

void ABadguyController::Tick(float DeltaTime)
{
    
    if (!IsValid(guy))
        //No pawn to control
        return;

    targetLoc = cb->GetActorLocation();
    guy->LookAt(targetLoc);
    
    if (!inPath)
    {
        DoPath(targetLoc);
        inPath = true;
    }
}

void ABadguyController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Move Completed"));
    Super::OnMoveCompleted(RequestID, Result);

    if (Result.IsSuccess())
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Move completed successfully."));
    }
    else if (Result.IsFailure())
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Move failed."));
    }
    else if (Result.IsInterrupted())
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Move was aborted."));
    }

    inPath = false;
}

void ABadguyController::DoPath_Implementation(FVector dest)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Attempting Path From C++"));

    UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, targetLoc);
}

//Getters for blueprint
bool ABadguyController::GetCanStrafe()
{
    return guy->CanStrafeWhileRunning;
}
float ABadguyController::GetShootingRange() 
{ 
    return guy->DesiredShootRange; 
}

float ABadguyController::GetMaxHealth() 
{ 
    return guy->MaxHealth; 
}