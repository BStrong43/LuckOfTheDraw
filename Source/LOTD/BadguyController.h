// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BadguyController.generated.h"

/**
 * 
 */
class ABadguy;
class ACowboyCharacter;

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

private:
	FVector targetLoc;
	ABadguy* guy;
	ACowboyCharacter* cb;
	bool inPath = false;
};
