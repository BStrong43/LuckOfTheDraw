// Fill out your copyright notice in the Description page of Project Settings.


#include "Magazine.h"

// Sets default values for this component's properties
UMagazine::UMagazine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	LoadProjectilePool();
}

void UMagazine::LoadDefaultEnemyMagazine()
{
	mag.Empty();
	mag.Add(0);
	MagSize = 1;
}

void UMagazine::LoadDefaultCowboyMagazine()
{
	mag.Add(0);
	mag.Add(0);
	mag.Add(0);
	mag.Add(0);
	mag.Add(0);
	mag.Add(0);
}

void UMagazine::LoadProjectilePool()
{
	ProjectilePool.Add(ABullet::StaticClass());
}


// Called when the game starts
void UMagazine::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UMagazine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


TSubclassOf<ABullet> UMagazine::ShootChamberedBullet()
{
	int chambered = mag[0];

	mag.RemoveAt(0);
	mag.Push(chambered);

	return ProjectilePool[chambered];
}

void UMagazine::FillMag(int b)
{

}