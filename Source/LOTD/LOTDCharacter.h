// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "Bullet.h"
#include "Magazine.h"
#include "Logging/LogMacros.h"
#include "LOTDCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class LOTD_API ALOTDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RollAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootHoldAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootReleaseAction;

	//THE GUN
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UMagazine* Mag;




public:
	ALOTDCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float CursorSensitivity = 1.0f;

protected:

	/** Called for movement input */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character Actions")
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character Actions")
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character Actions")
	void Shoot();

	void LookAtLocation(const FVector& TargetLocation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character Actions")
	void Roll();


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	FVector2D AimVector;
	float CursorMaxDistance = 150;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

