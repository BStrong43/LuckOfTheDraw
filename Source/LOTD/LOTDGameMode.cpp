// Copyright Epic Games, Inc. All Rights Reserved.

#include "LOTDGameMode.h"
#include "LOTD_GameStateBase.h"
#include "CowboyCharacter.h"
#include "CowboyController.h"
#include "UObject/ConstructorHelpers.h"

ALOTDGameMode::ALOTDGameMode()
{
	DefaultPawnClass = ACowboyCharacter::StaticClass();
	PlayerControllerClass = ACowboyController::StaticClass();
	GameStateClass = ALOTD_GameStateBase::StaticClass();

	LoadProjectilePool();
}

void ALOTDGameMode::LoadProjectilePool()
{
	ProjectilePool.Add(ABullet::StaticClass());
}