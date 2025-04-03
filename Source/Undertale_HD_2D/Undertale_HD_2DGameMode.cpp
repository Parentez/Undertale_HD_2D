// Copyright Epic Games, Inc. All Rights Reserved.

#include "Undertale_HD_2DGameMode.h"
#include "Undertale_HD_2DCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUndertale_HD_2DGameMode::AUndertale_HD_2DGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
