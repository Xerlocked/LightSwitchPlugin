// Copyright Epic Games, Inc. All Rights Reserved.

#include "XLightSwitchCommands.h"

#define LOCTEXT_NAMESPACE "FXLightSwitchModule"

void FXLightSwitchCommands::RegisterCommands()
{
	UI_COMMAND(LightAction, "XLightSwitch", "Directional Light Switch", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
