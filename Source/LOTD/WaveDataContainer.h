// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Badguy.h"
#include "Engine/DataAsset.h"
#include "WaveDataContainer.generated.h"



USTRUCT(BlueprintType)
struct FEnemyWaveInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Data")
    TSubclassOf<class ABadguy> EnemyClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Data")
    int32 TotalToSpawn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Data")
    int32 MaxConcurrentEnemies;
};

/**
 * 
 */
UCLASS(BlueprintType)
class LOTD_API UWaveDataContainer : public UDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FEnemyWaveInfo> EnemyWaves;
};
