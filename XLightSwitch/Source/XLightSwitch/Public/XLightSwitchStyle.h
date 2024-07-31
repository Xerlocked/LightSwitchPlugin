// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FXLightSwitchStyle
{
public:

	static void Initialize();

	static void Shutdown();
	
	static void ReloadTextures();
	
	static const ISlateStyle& Get();

	static FName GetStyleSetName();

	static void UpdateIcons(bool bNewState);

private:

	static TSharedRef<FSlateStyleSet> Create();
	static TSharedPtr<FSlateStyleSet> StyleInstance;

	static TSharedPtr<FSlateImageBrush> LightOnBrush;
	static TSharedPtr<FSlateImageBrush> LightOffBrush;
};