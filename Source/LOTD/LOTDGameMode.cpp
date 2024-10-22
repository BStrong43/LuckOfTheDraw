// Copyright Epic Games, Inc. All Rights Reserved.

#include "LOTDGameMode.h"
#include "LOTDCharacter.h"
#include "CowboyController.h"
#include "UObject/ConstructorHelpers.h"

ALOTDGameMode::ALOTDGameMode()
{
	DefaultPawnClass = ACowboyCharacter::StaticClass();
	PlayerControllerClass = ACowboyController::StaticClass();
}
