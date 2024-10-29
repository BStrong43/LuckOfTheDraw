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

UENUM(BlueprintType)
enum class EEnemyAction : uint8
{
	Reloading    UMETA(DisplayName = "Reloading"),
	Moving       UMETA(DisplayName = "Moving"),
	Shooting     UMETA(DisplayName = "Shooting")
};


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

	//Status of badguy pathing
	EEnemyAction CurrentAction;
	bool inPath = false;
	float shootTime, reloadTime;
};
