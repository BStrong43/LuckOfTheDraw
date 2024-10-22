// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CowboyCharacter.h"
#include "GameFramework/PlayerController.h"
#include "CowboyController.generated.h"

/**
 * 
 */
UCLASS()
class LOTD_API ACowboyController : public APlayerController
{
	GENERATED_BODY()
	ACowboyController();

public:
	virtual void SetupInputComponent() override;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	void HandleMouseLook(const FInputActionValue& Value);
	void HandleMovement(const FInputActionValue& Value);
	void HandleDodge();
	void HandleShoot();

public:
	//Input Mapping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cowboy|Input")
	UInputMappingContext* InputMapping;

	// Enhanced Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cowboy|Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cowboy|Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cowboy|Input")
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cowboy|Input")
	UInputAction* DodgeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cowboy|Input")
	float CursorDistance = 200;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cowboy|Input")
	float LookSensitivity = 8;
	
private:
	FVector cursorLoc;
	ACowboyCharacter* cb;
};
