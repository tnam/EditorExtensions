// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FEditorExtensionPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	void RegisterWebAssetActions();
	void UnregisterWebAssetActions();

	void RegisterToolbarExtension();
	void UnregisterToolbarExtension();
	void AddToolbarExtension(class FToolBarBuilder &Builder);

	void RegisterMenuExtension();
	void UnregisterMenuExtension();
	void AddMenuExtension(class FMenuBuilder &Builder);

	void OpenBrowserWindow();

	void RegisterSettings();
	void UnregisterSettings();

	void RegisterDetailsCustomizations();
	void UnregisterDetailsCustomizations();

	void RegisterConsoleCommand();
	void UnregisterConsoleCommand();

private:

	TArray< TSharedPtr<class IAssetTypeActions> > CreatedAssetTypeActions;
	TSharedPtr<FExtender> ToolbarExtender;
	TSharedPtr<const FExtensionBase> ToolbarExtension;
	TSharedPtr<FExtender> MenuExtender;
	TSharedPtr<const FExtensionBase> MenuExtension;
	IConsoleCommand* DisplayWindowCommand;
};
