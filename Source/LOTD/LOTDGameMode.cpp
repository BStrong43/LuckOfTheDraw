// Copyright Epic Games, Inc. All Rights Reserved.

#include "LOTDGameMode.h"
#include "LOTD_GameStateBase.h"
#include "WaveManager.h"
#include "Bullet.h"
#include "CowboyCharacter.h"
#include "CowboyController.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "AssetRegistry/AssetRegistryModule.h"


ALOTDGameMode::ALOTDGameMode()
{
	DefaultPawnClass = ACowboyCharacter::StaticClass();
	PlayerControllerClass = ACowboyController::StaticClass();
	GameStateClass = ALOTD_GameStateBase::StaticClass();

	LoadProjectilePool();
}

void ALOTDGameMode::LoadProjectilePool()
{
    ProjectilePool.Empty();

    ProjectilePool.Add(ABullet::StaticClass());
}


void ALOTDGameMode::LoadProjectilePoolRecursive() //This does not work currently :(
{
	ProjectilePool.Empty();

	ProjectilePool.Add(ABullet::StaticClass());

    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

    // Define the class and path filters
    FARFilter Filter;
    Filter.ClassNames.Add(UBlueprint::StaticClass()->GetFName());
    Filter.bRecursivePaths = true;
    Filter.PackagePaths.Add("/Game/ThirdPerson/Blueprints/Bullets"); // Specify your folder path here, like "/Game/Blueprints"

    // Search the asset registry
    TArray<FAssetData> AssetDataList;
    AssetRegistryModule.Get().GetAssets(Filter, AssetDataList);

    for (const FAssetData& AssetData : AssetDataList)
    {
        // Load the Blueprint object
        UBlueprint* Blueprint = Cast<UBlueprint>(AssetData.GetAsset());
        if (Blueprint && Blueprint->GeneratedClass && Blueprint->GeneratedClass->IsChildOf(ABullet::StaticClass()))
        {
            // Add the class to ProjectilePool
            // This line dont work
            //ProjectilePool.Add(Cast<TSubclassOf<ABullet>>(Blueprint->GeneratedClass));
        }
    }
}

void ALOTDGameMode::Tick(float DeltaTime)
{

}

void ALOTDGameMode::BeginPlay()
{
    SetUpWaveManager();
}

void ALOTDGameMode::SetUpWaveManager()
{
    AActor* a = UGameplayStatics::GetActorOfClass(GetWorld(), AWaveManager::StaticClass());
    
    if (a) WaveManager = Cast<AWaveManager>(a);

    if (IsValid(WaveManager))
    {
        TArray<AActor*> potentialpoints;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnPoint::StaticClass(), potentialpoints);

        for (int i = 0; i < potentialpoints.Num(); i++)
        {
            WaveManager->AddSpawnPoint(potentialpoints[i]);
        }
    }
}