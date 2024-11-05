// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "EnemySpawnPoint.h"
#include "GameFramework/GameModeBase.h"
#include "LOTDGameMode.generated.h"

class ABullet;
class AWaveManager;


UCLASS(minimalapi)
class ALOTDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALOTDGameMode();
	inline TSubclassOf<ABullet> GetProjectileFromPool(int index) { return ProjectilePool[index]; }

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);

	UPROPERTY(VisibleAnywhere, Category = "Pooled Data")
	AWaveManager* WaveManager;

	UPROPERTY(VisibleAnywhere, Category = "Pooled Data")
	TArray<TSubclassOf<ABullet>> ProjectilePool;

private:
	void LoadProjectilePool();
	void LoadProjectilePoolRecursive();

	void SetUpWaveManager();
};



