// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CowboyMovementComponent.h"
#include "Magazine.h"
#include "Bullet.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CowboyCharacter.generated.h"

UCLASS()
class LOTD_API ACowboyCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACowboyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount,
		FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	//Character Actions
	UFUNCTION(BlueprintCallable, Category = "Cowboy|Actions")
	void Shoot();
	UFUNCTION(BlueprintCallable, Category = "Cowboy|Actions")
	void Dodge();

public:
	//cb Blueprint Events
	
	//Used to maintain proper Look Rotation
	UFUNCTION(BlueprintCallable, Category = "Cowboy|Actions")
	void Look(FVector point);
	
	//Called when the cowboy shoots
	UFUNCTION(BlueprintNativeEvent, Category = "Cowboy|Actions")
	void OnShoot(ABullet* shot);

	//Called when cowboy dodges
	UFUNCTION(BlueprintNativeEvent, Category = "Cowboy|Actions")
	void OnDodge();

	UFUNCTION(BlueprintImplementableEvent, Category = "Cowboy|Actions")
	void OnDie();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cowboy|Character")
	float MaxHealth = 30;

public:
	///Components___________________________________________________________

	//Cowboys Collision Detections
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cowboy|Collision")
	UCapsuleComponent* Collider;

	//Invisible arm for the camera.  Manages camera placement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cowboy|Camera")
	USpringArmComponent* SpringArm;

	//Game Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cowboy|Camera")
	UCameraComponent* Camera;

	//Manages Cowboys Movement Physics
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Cowboy|Movement")
	UCowboyMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cowboy|Character")
	USkeletalMeshComponent* CowboyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cowboy|Gun")
	UMagazine* Mag;

private:
	float recoilTime = 0;
	float health;

	void Die();
};
