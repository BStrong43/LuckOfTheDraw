// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "BadguyController.h"
#include "Magazine.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Badguy.generated.h"


UCLASS()
class LOTD_API ABadguy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABadguy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual UPawnMovementComponent* GetMovementComponent() const override;
	void LookAt(FVector point);

	//Destroying Actor is already handled
	UFUNCTION(BlueprintImplementableEvent, Category = "Badguy|Events")
	void OnDie();

	//Tell Badguy to 
	UFUNCTION(BlueprintCallable, Category = "Badguy|Actions")
	void Shoot();

	//Called when Badguy shoots. Use to apply effects to the shot
	UFUNCTION(BlueprintImplementableEvent, Category = "Badguy|Actions")
	void OnShoot(ABullet* shot);

	UFUNCTION(BlueprintCallable, Category = "Badguy|Character")
	void Heal(int healAmount);

	UFUNCTION(BlueprintCallable, Category = "Badguy|Character")
	bool HasLineOfSightToPawn(APawn* OtherPawn);


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Badguy|Movement")
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Badguy|Character")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Badguy|Collision")
	UCapsuleComponent* Collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Badguy|Gun")
	UMagazine* Mag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Badguy|Character")
	float MaxHealth = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Badguy|Character")
	float RunSpeed = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Badguy|Character")
	float DesiredShootRange = 600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Badguy|Character")
	float ReloadTime = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Badguy|Character")
	float TimeBetweenShots = 0.57f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Badguy|Character")
	bool CanStrafeWhileRunning = true;

private:

	void RunShootTimer();

	void Die();
	float health;
	float recoilTime = 0;
};