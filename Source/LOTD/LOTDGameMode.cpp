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


//Failed attempt to recursively load all bullet bp's from a single folder
//Currently not in use
void ALOTDGameMode::LoadProjectilePoolRecursive()
{
    /*
	ProjectilePool.Empty();

	ProjectilePool.Add(ABullet::StaticClass());

    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

    // Define the class and path filters
    FARFilter Filter;
    Filter.ClassNames.Add(UBlueprint::StaticClass()->GetFName());
    Filter.bRecursivePaths = true;
    Filter.PackagePaths.Add("/Game/ThirdPerson/Blueprints/Bullets");

    // Search the asset registry
    TArray<FAssetData> AssetDataList;
    AssetRegistryModule.Get().GetAssets(Filter, AssetDataList);

    for (const FAssetData& AssetData : AssetDataList)
    {
        // Load the Blueprint object
        UBlueprint* Blueprint = Cast<UBlueprint>(AssetData.GetAsset());
        if (Blueprint && Blueprint->GeneratedClass && Blueprint->GeneratedClass->IsChildOf(ABullet::StaticClass()))
        {
            //Add the class to ProjectilePool
            //This line dont work :(
            //ProjectilePool.Add(Cast<TSubclassOf<ABullet>>(Blueprint->GeneratedClass->StaticClass()));
        }
    }
    */
}

void ALOTDGameMode::Tick(float DeltaTime)
{

}

void ALOTDGameMode::BeginPlay()
{

}

void ALOTDGameMode::SetUpWaveManager()
{
    AActor* a = UGameplayStatics::GetActorOfClass(GetWorld(), AWaveManager::StaticClass());
    
    if (a)
        WaveManager = Cast<AWaveManager>(a);

    if (IsValid(WaveManager))
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Emerald, TEXT("WaveManager Found"));

        TArray<AActor*> potentialpoints;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnPoint::StaticClass(), potentialpoints);

        for (int i = 0; i < potentialpoints.Num(); i++)
        {
            WaveManager->AddSpawnPoint(potentialpoints[i]);
        }
    }
}

void ALOTDGameMode::LoadProjectilePool()
{
    ProjectilePool.Empty();

    ProjectilePool.Add(ABullet::StaticClass());
/*
    TSubclassOf<ABullet> b;

    static ConstructorHelpers::FObjectFinder<ABullet> Fireball(TEXT("Bullet'/Game/ThirdPerson/Blueprints/Bullets/Fireball.Fireball'"));

    if (Fireball.Succeeded())
    {
        ProjectilePool.Add(Fireball.Object->StaticClass());
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("COULD NOT LOAD FIREBALL"));
    }
*/
}