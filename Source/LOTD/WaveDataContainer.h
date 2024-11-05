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

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<ABadguy> EnemyType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int Quantity;
};

/**
 * 
 */
UCLASS(BlueprintType)
class LOTD_API UWaveDataContainer : public UPrimaryDataAsset
{
	GENERATED_BODY()
	UWaveDataContainer();

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FEnemyWaveInfo> EnemyWaves;
};
