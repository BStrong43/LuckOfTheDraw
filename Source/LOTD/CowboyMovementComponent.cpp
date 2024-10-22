// Fill out your copyright notice in the Description page of Project Settings.


#include "CowboyMovementComponent.h"

void UCowboyMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // Ensure we can move
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    // Calculate exact distance to travel from Pawn's input vectors
    FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * MoveSpeed * DeltaTime;
    
    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
        // Move the component safely, handling collisions
        FHitResult Hit;
        SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit, ETeleportType::ResetPhysics);

        // Handle collision response
        if (Hit.IsValidBlockingHit())
        {
            SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit, true);
        }
    }
}