// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Bullet.h"
#include "Magazine.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOTD_API UMagazine : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMagazine();

	UFUNCTION(BlueprintCallable, Category = "Mag")
	void FillMag(int b);

	UFUNCTION(BlueprintCallable, Category = "Mag")
	TSubclassOf<ABullet> ShootChamberedBullet();

	UFUNCTION(BlueprintCallable, Category = "Mag")
	void LoadDefaultMagazine();

	UPROPERTY(EditAnywhere, Category = "Mag")
	TArray<int> mag;

	UPROPERTY(EditAnywhere, Category = "Mag")
	TArray<TSubclassOf<ABullet>> ProjectilePool;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "Mag")
	int MagSize = 6;

private:
	inline int CheckChamberedBullet() { return mag[0]; }
	void LoadProjectilePool();

};
