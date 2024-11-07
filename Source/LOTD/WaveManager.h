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

	void StartWave();
	void EndWave();
	void PauseWave();
	void OnEnemyDeath(TSubclassOf<ABadguy> EnemyClass);

	void AddSpawnPoint(AActor* point);

	UPROPERTY(EditAnywhere)
	UWaveDataContainer* WaveData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnInitialEnemies();
	void TrySpawnEnemy(TSubclassOf<ABadguy> EnemyClass);

	void SpawnTimerTick();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> SpawnPoints;
	
	FTimerHandle SpawnTimer;

	TMap<TSubclassOf<ABadguy>, int32> ActiveEnemiesCount;
	TMap<TSubclassOf<ABadguy>, int32> TotalSpawnedCount;

	AActor* GetRandomSpawnLoc();
	int TrackEnemyCount(ABadguy* Enemy);
};
