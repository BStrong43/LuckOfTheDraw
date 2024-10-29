// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
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

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Badguy|Actions")
	void DoPath(FVector Loc);

	UFUNCTION(BlueprintCallable, Category = "Badguy|Character")
	float GetShootingRange();

	UFUNCTION(BlueprintCallable, Category = "Badguy|Character")
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Badguy|Character")
	bool GetCanStrafe();

	UFUNCTION(BlueprintCallable, Category = "Badguy|Character")
	inline ABadguy* GetGuy() { return guy; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);
	
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

private:
	//DEBUG
	bool IsNavDataValidForPawn();

	
	//Reference to Badguy being controlled
	ABadguy* guy;

	//Player Reference
	ACowboyCharacter* cb;

	//Location badguy will path to
	FVector targetLoc;

	//Status of badguy pathing
	bool inPath = false;
};
