// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Bullet.generated.h"

UENUM(BlueprintType) // Allows the enum to be used in Blueprints
enum class EDamageType : uint8
{
	PT_Default    UMETA(DisplayName = "Default"),
	PT_Fire       UMETA(DisplayName = "Fire"),
	PT_Ice        UMETA(DisplayName = "Ice"),
	PT_Electric   UMETA(DisplayName = "Electric"),
	PT_Explosive   UMETA(DisplayName = "Explosive"),
	PT_Max        UMETA(Hidden) // Use this to represent the maximum value
};

UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	BULLET    UMETA(DisplayName = "Bullet"),
	GRENADE   UMETA(DisplayName = "Grenade"),
	BUFF      UMETA(DisplayName = "Buff")
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

	UFUNCTION(BlueprintImplementableEvent, Category = "Bullet|Events")
	void OnFire();

	UFUNCTION(BlueprintImplementableEvent, Category = "Bullet|Events")
	void DoExplode(FHitResult hit);

	//Call this in blueprint to implement 
	UFUNCTION(BlueprintImplementableEvent, Category = "Bullet|Events")
	void ExtraTick(float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void BulletTick(float DeltaTime);
	void BuffTick(float DeltaTime);
	void GrenadeTick(float DeltaTime);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet|Properties")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet|Properties")
	USphereComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet|Properties")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Bullet|Stats")
	EProjectileType ProjectileType;

	UPROPERTY(EditAnywhere, Category = "Bullet|Stats")
	EDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet|Stats")
	float RecoilTime = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet|Stats")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet|Stats")
	float ProjectileSpeed = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet|Stats")
	bool DestroyOnEnemyHit = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet|Stats")
	bool TrackDistance = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet|Stats")
	float ProjectileRange = 1500;

private:
	FVector movementDirection;
	float distanceCovered;

	float maximumTimeAlive = 60.f;
};
