// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveDataContainer.h"
#include "WaveManager.generated.h"


UCLASS()
class LOTD_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveManager();

	UPROPERTY(EditAnywhere)
	int MaxEnemies;

	void StartWave();
	void EndWave();
	void PauseWave();
	void EnemyDied();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UWaveDataContainer* WaveData;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> SpawnPoints;

	int CurrentWaveIndex = 0;
	int ActiveEnemyCount = 0;

	void SpawnNextEnemy();
	void TrackEnemyCount(ABadguy* Enemy);

};
