// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaveManager::StartWave()
{
    if (CurrentWaveIndex < WaveData->EnemyWaves.Num())
    {
        // Reset counters and start spawning for the wave
        ActiveEnemyCount = 0;
        SpawnNextEnemy();
    }
}

void AWaveManager::EndWave()
{
    // Perform actions like resetting indices or triggering events
    CurrentWaveIndex = 0;
    ActiveEnemyCount = 0;
}

void AWaveManager::PauseWave()
{

}

void AWaveManager::EnemyDied()
{
    ActiveEnemyCount--;

    if (ActiveEnemyCount < MaxEnemies)
    {
        SpawnNextEnemy();
    }

    // Check if all enemies in the wave are defeated
    if (ActiveEnemyCount == 0 && CurrentWaveIndex >= WaveData->EnemyWaves.Num())
    {
        EndWave();
    }
}

void AWaveManager::TrackEnemyCount(ABadguy* EnemyType)
{

}

void AWaveManager::SpawnNextEnemy()
{
    if (ActiveEnemyCount >= MaxEnemies)
        return;

    const FEnemyWaveInfo& WaveInfo = WaveData->EnemyWaves[CurrentWaveIndex];

    if (WaveInfo.Quantity > 0)
    {
        AActor* SpawnPoint = SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)];
        FActorSpawnParameters SpawnParams;
        ABadguy* SpawnedEnemy = GetWorld()->SpawnActor<ABadguy>(WaveInfo.EnemyType, SpawnPoint->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);

        if (SpawnedEnemy)
        {
            TrackEnemyCount(SpawnedEnemy);
            ActiveEnemyCount++;
        }
    }
    else
    {
        CurrentWaveIndex++;
        StartWave();
    }
}