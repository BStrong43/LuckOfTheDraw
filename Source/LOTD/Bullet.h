// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Bullet.generated.h"

UENUM(BlueprintType) // Allows the enum to be used in Blueprints
enum class EProjectileType : uint8
{
	PT_Default    UMETA(DisplayName = "Default"),
	PT_Fire       UMETA(DisplayName = "Fire"),
	PT_Ice        UMETA(DisplayName = "Ice"),
	PT_Electric   UMETA(DisplayName = "Electric"),
	PT_Explosive   UMETA(DisplayName = "Explosive"),
	PT_Max        UMETA(Hidden) // Use this to represent the maximum value
};

UCLASS()
class LOTD_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
	float ProjectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
	float ProjectileRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Properties")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
	float RecoilTime = 0.57f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile Properties")
	EProjectileType bDamageType;

private:


	FVector movementDirection;
	float distanceCovered;
};
