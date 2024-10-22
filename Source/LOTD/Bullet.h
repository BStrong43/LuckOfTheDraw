// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetCollisionAsEnemy();
	void SetCollisionAsCowboy();
	void OnWallHit(FHitResult hit);

	UFUNCTION(BlueprintImplementableEvent, Category = "Projectile Properties")
	void DoExplode(FHitResult hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Properties")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Properties")
	USphereComponent* Collider;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile Properties")
	EProjectileType bDamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
	float RecoilTime = 0.57f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
	float ProjectileSpeed = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
	bool TrackDistance = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
	float ProjectileRange = 1500;

private:
	FVector movementDirection;
	float distanceCovered;

	void HandleHit(FHitResult hit);
};
