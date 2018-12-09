// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EditorExtensionPlugin.h"

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "AssetToolsModule.h"

#include "WebAssetActions.h"

#define LOCTEXT_NAMESPACE "FEditorExtensionPluginModule"

void FEditorExtensionPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	RegisterWebAssetActions();
}

void FEditorExtensionPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UnregisterWebAssetActions();
}

void FEditorExtensionPluginModule::RegisterWebAssetActions()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	auto Actions = MakeShareable(new FWebAssetActions);
	AssetTools.RegisterAssetTypeActions(Actions);
	CreatedAssetTypeActions.Add(Actions);
}

void FEditorExtensionPluginModule::UnregisterWebAssetActions()
{
	FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");

	if (AssetToolsModule)
	{
		IAssetTools& AssetTools = AssetToolsModule->Get();
		for (auto Action : CreatedAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action.ToSharedRef());
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorExtensionPluginModule, EditorExtensionPlugin)