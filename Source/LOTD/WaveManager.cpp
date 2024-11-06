// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

// Sets default values
AWaveManager::AWaveManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

    if (false)
    {
        StartWave();
        GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AWaveManager::SpawnTimerTick, 5.0, true, 1.f);
    }
    
}

void AWaveManager::Tick(float DeltaTime)
{

}

void AWaveManager::SpawnTimerTick() 
{


}

void AWaveManager::StartWave()
{
    GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Emerald, GetName() + FString("Round Started"));

    SpawnInitialEnemies();
}

void AWaveManager::EndWave()
{
    GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Emerald, GetName() + FString("Round Finished"));
}

void AWaveManager::PauseWave()
{

}

void AWaveManager::OnEnemyDeath(TSubclassOf<ABadguy> EnemyClass)
{
    if (ActiveEnemiesCount.Contains(EnemyClass))
    {
        ActiveEnemiesCount[EnemyClass]--;

        // Check if more enemies of this type should be spawned
        if (ActiveEnemiesCount[EnemyClass] < 3 && TotalSpawnedCount[EnemyClass] < WaveData->EnemyWaves.FindByPredicate([EnemyClass](const FEnemyWaveInfo& Data) {
            return Data.EnemyClass == EnemyClass;
            })->TotalToSpawn)
        {
            TrySpawnEnemy(EnemyClass);
        }
    }
}

void AWaveManager::SpawnInitialEnemies()
{
    for (const FEnemyWaveInfo& Wave : WaveData->EnemyWaves)
    {
        int32 InitialSpawnCount = FMath::Min(Wave.TotalToSpawn, Wave.MaxConcurrentEnemies);
        TotalSpawnedCount.Add(Wave.EnemyClass, 0);
        ActiveEnemiesCount.Add(Wave.EnemyClass, 0);

        for (int32 i = 0; i < InitialSpawnCount; ++i)
        {
            TrySpawnEnemy(Wave.EnemyClass);
        }
    }
}

void AWaveManager::TrySpawnEnemy(TSubclassOf<ABadguy> EnemyClass)
{
    // Get an available spawn point
    if (SpawnPoints.Num() == 0)
        return;

    int32 RandomIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
    AActor* SpawnPoint = SpawnPoints[RandomIndex];

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ABadguy* SpawnedEnemy = GetWorld()->SpawnActor<ABadguy>(EnemyClass, SpawnPoint->GetActorLocation(), SpawnPoint->GetActorRotation(), SpawnParams);
    if (SpawnedEnemy)
    {
        ActiveEnemiesCount[EnemyClass]++;
        TotalSpawnedCount[EnemyClass]++;

        // Bind a delegate or event for enemy death
        SpawnedEnemy->OnDeath.AddDynamic(this, &AWaveManager::OnEnemyDeath);
    }
}

AActor* AWaveManager::GetRandomSpawnLoc()
{
    return SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)];
}

int AWaveManager::TrackEnemyCount(ABadguy* EnemyClass)
{
    return 0;
}

void AWaveManager::AddSpawnPoint(AActor* point)
{
    SpawnPoints.Add(point);
}