// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "BadguyController.h"
#include "Magazine.h"
#include "CowboyMovementComponent.h"
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

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Destroying Actor is already handled
	UFUNCTION(BlueprintImplementableEvent, Category = "Badguy|Events")
	void OnDie();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Badguy|Character")
	float MaxHealth = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Badguy|Character")
	float RunSpeed = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Badguy|Movement")
	UCowboyMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Badguy|Character")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Badguy|Collision")
	UCapsuleComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Badguy|Gun")
	UMagazine* Mag;

private:
	void Die();

	float health;
};
