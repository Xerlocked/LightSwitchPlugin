// Copyright Epic Games, Inc. All Rights Reserved.

#include "XLightSwitch.h"

#include "EngineUtils.h"
#include "XLightSwitchStyle.h"
#include "XLightSwitchCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Components/LightComponent.h"
#include "Engine/DirectionalLight.h"

static const FName XLightSwitchTabName("XLightSwitch");

#define LOCTEXT_NAMESPACE "FXLightSwitchModule"
bool FXLightSwitchModule::bLightSwitch = true;

void FXLightSwitchModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FXLightSwitchStyle::Initialize();
	FXLightSwitchStyle::ReloadTextures();

	FXLightSwitchCommands::Register();
	
	LightCommands = MakeShareable(new FUICommandList);

	LightCommands->MapAction(
		FXLightSwitchCommands::Get().LightAction,
		FExecuteAction::CreateRaw(this, &FXLightSwitchModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FXLightSwitchModule::RegisterMenus));
}

void FXLightSwitchModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FXLightSwitchStyle::Shutdown();

	FXLightSwitchCommands::Unregister();
}

void FXLightSwitchModule::PluginButtonClicked()
{
	ExecuteLight();
}

void FXLightSwitchModule::ExecuteLight()
{
	if(HasDirectionalLight())
	{
		bLightSwitch = !bLightSwitch;
		
		TObjectPtr<ADirectionalLight> DirectionalLight = GetDirectionalLight();

		DirectionalLight->GetLightComponent()->SetVisibility(bLightSwitch);
		
		FXLightSwitchStyle::UpdateIcons(bLightSwitch);
	}
}

bool FXLightSwitchModule::HasDirectionalLight()
{
	UWorld* World = nullptr;

	if (GEditor)
	{
		World = GEditor->GetEditorWorldContext().World();
	}

	if (World)
	{
		for (TActorIterator<ADirectionalLight> It(World); It; ++It)
		{
			if (*It)
			{
				return true;
			}
		}
	}

	return false;
}

TObjectPtr<ADirectionalLight> FXLightSwitchModule::GetDirectionalLight()
{
	if (GEditor)
	{
		UWorld* World = GEditor->GetEditorWorldContext().World();
		if (World)
		{
			for (TActorIterator<ADirectionalLight> It(World); It; ++It)
			{
				if (*It)
				{
					return *It;
				}
			}
		}
	}
	return nullptr;
}

void FXLightSwitchModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);
	
	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FXLightSwitchCommands::Get().LightAction));
				Entry.SetCommandList(LightCommands);
			}
		}
	}
}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FXLightSwitchModule, XLightSwitch)