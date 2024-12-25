// Copyright Epic Games, Inc. All Rights Reserved.

#include "MeleeFighterGameMode.h"
#include "MeleeFighterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMeleeFighterGameMode::AMeleeFighterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
