// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"

#include "GameFramework/GameModeBase.h"
#include "LOTDGameMode.generated.h"

UCLASS(minimalapi)
class ALOTDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALOTDGameMode();
	inline TSubclassOf<ABullet> GetProjectileFromPool(int index) { return ProjectilePool[index]; }

protected:
	UPROPERTY(EditAnywhere, Category = "Pooled Data")
	TArray<TSubclassOf<ABullet>> ProjectilePool;

private:
	void LoadProjectilePool();
};



