// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "BadguyController.generated.h"

/**
 * 
 */
class ABadguy;
class ACowboyCharacter;
class UNavigationSystemV1;
class UNavigationPath;


UCLASS()
class LOTD_API ABadguyController : public AAIController
{
	GENERATED_BODY()

	ABadguyController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);
	
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	virtual UNavigationPath* CalculatePath();

	UNavigationSystemV1* NavSystem;
	UPathFollowingComponent* PathFollower;

private:
	
	//Reference to Badguy being controlled
	ABadguy* guy;

	//Player Reference
	ACowboyCharacter* cb;

	//Location badguy will path to
	FVector targetLoc;

	//Status of badguy pathing
	bool inPath = false;

	//Current path badguy is taking
	UNavigationPath* path;
};
