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

    PathFollower = CreateDefaultSubobject<UPathFollowingComponent>(TEXT("Path Follower"));
    SetPathFollowingComponent(PathFollower);
}

void ABadguyController::BeginPlay()
{
    Super::BeginPlay();

    cb = Cast<ACowboyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

    if(IsValid(NavSystem))
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Nav System Found"));

}

void ABadguyController::OnPossess(APawn* InPawn)
{
    SetPawn(InPawn);
    guy = Cast<ABadguy>(InPawn);
    
    if (IsValid(guy))
    {
        PathFollower->SetMovementComponent(guy->GetMovementComponent());
        PathFollower->SetAcceptanceRadius(guy->DesiredShootRange);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, GetName() + FString(" Could not possess badguy"));
    }
}

void ABadguyController::OnUnPossess()
{
    Super::UnPossess();
}

void ABadguyController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (!IsValid(guy))
        //No pawn to control
        return;

    
    if (!inPath)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Attempting Path"));
        targetLoc = cb->GetActorLocation();
        path = NavSystem->FindPathToLocationSynchronously(GetWorld(), guy->GetActorLocation(), targetLoc);

        if (path)
        {
            PathFollower->RequestMove(FAIMoveRequest(targetLoc), path->GetPath());
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, GetName() + FString(" NULL Path"));
        }

        inPath = true;
    }
}

void ABadguyController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Move Completed"));
    Super::OnMoveCompleted(RequestID, Result);

    inPath = false;
}

UNavigationPath* ABadguyController::CalculatePath() 
{
    return nullptr;
}