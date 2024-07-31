// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "XLightSwitchStyle.h"

class FXLightSwitchCommands : public TCommands<FXLightSwitchCommands>
{
public:

	FXLightSwitchCommands()
		: TCommands<FXLightSwitchCommands>(TEXT("XLightSwitch"), NSLOCTEXT("Contexts", "XLightSwitch", "XLightSwitch Plugin"), NAME_None, FXLightSwitchStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > LightAction;
};
