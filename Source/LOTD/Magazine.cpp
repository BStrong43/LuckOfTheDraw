// Fill out your copyright notice in the Description page of Project Settings.


#include "Magazine.h"

// Sets default values for this component's properties
UMagazine::UMagazine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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

	ALOTDGameMode* game = Cast<ALOTDGameMode>(GetWorld()->GetAuthGameMode());
	TSubclassOf<ABullet> proj;

	if (IsValid(game))
	{
		proj = game->GetProjectileFromPool(chambered);
	}
	else //Invalid GameMode
	{
		//Use default bullet
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Projectile Pool Inaccessible"));
		proj = ABullet::StaticClass();
	}

	return proj;
}

void UMagazine::FillMag(int b)
{
	mag.Empty();

	for (int i = 0; i < MagSize; i++)
		mag.Add(b);
}