// Fill out your copyright notice in the Description page of Project Settings.


#include "BadguyController.h"
#include "Badguy.h"
#include "CowboyCharacter.h"
#include "Kismet/GameplayStatics.h"

//DEBUG HEADERS
#include "NavigationSystem.h"
#include "NavigationPath.h"

ABadguyController::ABadguyController()
{
    // Enable Tick for this controller
    PrimaryActorTick.bCanEverTick = true;
    PathTimer = FTimerHandle();
    
    SetPathFollowingComponent(GetPathFollowingComponent());
}

void ABadguyController::OnPossess(APawn* InPawn)
{
    guy = Cast<ABadguy>(InPawn);
    SetPawn(guy);
    guy->Controller = this;
    
    //I also have this in BeginPlay()
    //Necessary for BP Controller use (for some reason) 
    //if(!cb) cb = Cast<ACowboyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    
    if (IsValid(guy))
    {
        GetPathFollowingComponent()->SetAcceptanceRadius(guy->DesiredShootRange);
        GetPathFollowingComponent()->SetMovementComponent(guy->GetMovementComponent());
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Emerald, GetName() + FString("Could not possess badguy"));
    }
}

void ABadguyController::OnUnPossess()
{
    
}

void ABadguyController::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(PathTimer, this, &ABadguyController::DoPathWrapper, pathClockTime, true, 1.5f);
        //(TimerHandle, this, &AMyAIController::UpdateMovement, 1.0f, true);
}

void ABadguyController::Tick(float DeltaTime)
{
    targetLoc = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
    guy->LookAt(targetLoc);

   
}

void ABadguyController::DoPathWrapper()
{
    DoPath(targetLoc);
}

void ABadguyController::DoPath_Implementation(FVector dest)
{
    //GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Magenta, TEXT("Movement Started"));

    GetPathFollowingComponent()->SetAcceptanceRadius(guy->DesiredShootRange);
    GetPathFollowingComponent()->SetMovementComponent(guy->GetMovementComponent());

    MoveToLocation(dest, GetPathFollowingComponent()->GetAcceptanceRadius(), true, true);
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

bool ABadguyController::IsNavDataValidForPawn()
{
    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (!NavSystem)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Navigation System is not available in the world."));
        return false;
    }

    // Check if there is valid navigation data for the controller's pawn
    if (APawn* ControlledPawn = GetPawn())
    {
        // Retrieve the pawn's navigation agent properties
        const FNavAgentProperties& NavAgentProperties = ControlledPawn->GetNavAgentPropertiesRef();

        // Get the navigation data for these properties
        const ANavigationData* NavData = NavSystem->GetNavDataForProps(NavAgentProperties);
        if (NavData)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Valid navigation data found for the pawn."));
            return true;
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("No compatible navigation data found for the pawn's NavAgentProperties."));
            return false;
        }
    }

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Controller does not currently possess a pawn."));
    return false;
}

void ABadguyController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if (Result.IsSuccess())
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Move completed successfully."));
    }
    else if (Result.HasFlag(FPathFollowingResultFlags::OwnerFinished))
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Owner Finished"));
    }
    else if (Result.IsFailure())
    {
        GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Green, TEXT("Move failed."));
    }
    else if (Result.IsInterrupted())
    {
        GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, TEXT("Move was aborted."));
    }
    
}