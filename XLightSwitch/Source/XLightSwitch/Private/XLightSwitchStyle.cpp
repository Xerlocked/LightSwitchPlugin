// Copyright Epic Games, Inc. All Rights Reserved.

#include "XLightSwitchStyle.h"
#include "XLightSwitch.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FXLightSwitchStyle::StyleInstance = nullptr;
TSharedPtr<FSlateImageBrush> FXLightSwitchStyle::LightOnBrush = nullptr;
TSharedPtr<FSlateImageBrush> FXLightSwitchStyle::LightOffBrush = nullptr;

void FXLightSwitchStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FXLightSwitchStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FXLightSwitchStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("XLightSwitchStyle"));
	return StyleSetName;
}

/**
 * Toolbar 아이콘을 상태에 맞게 업데이트 합니다.
 * 
 * @param bNewState 새롭게 설정할 Directional Light의 상태값 
 */
void FXLightSwitchStyle::UpdateIcons(bool bNewState)
{
	if (StyleInstance.IsValid())
	{
		StyleInstance->Set("XLightSwitch.LightAction", bNewState ? LightOnBrush.Get() : LightOffBrush.Get());
	} 

	ReloadTextures();
}

TSharedRef< FSlateStyleSet > FXLightSwitchStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("XLightSwitchStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("XLightSwitch")->GetBaseDir() / TEXT("Resources"));

	LightOnBrush = MakeShareable(new IMAGE_BRUSH(TEXT("sun"), CoreStyleConstants::Icon24x24));
	LightOffBrush = MakeShareable(new IMAGE_BRUSH(TEXT("moon"), CoreStyleConstants::Icon24x24));
	
	Style->Set("XLightSwitch.LightAction", LightOnBrush.Get());
	return Style;
}

void FXLightSwitchStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FXLightSwitchStyle::Get()
{
	return *StyleInstance;
}
