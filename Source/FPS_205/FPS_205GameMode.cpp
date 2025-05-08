// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_205GameMode.h"
#include "FPS_205Character.h"
#include "UObject/ConstructorHelpers.h"

AFPS_205GameMode::AFPS_205GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
