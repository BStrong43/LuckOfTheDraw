// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "GameFramework/GameStateBase.h"
#include "LOTD_GameStateBase.generated.h"

/**
 * 
 */

UCLASS()
class LOTD_API ALOTD_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
	ALOTD_GameStateBase();

public:
	//inline TSubclassOf<ABullet> GetProjectileFromPool(int index) { return ProjectilePool[index]; };

private:
	//void LoadProjectilePool();
	//TArray<TSubclassOf<ABullet>> ProjectilePool;
};
