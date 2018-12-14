// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EditorExtensionPlugin.h"

#include "Modules/ModuleManager.h"
#include "Editor/MainFrame/Public/Interfaces/IMainFrameModule.h"
#include "AssetToolsModule.h"
#include "EditorStyleSet.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Framework/Application/SlateApplication.h"
#include "LevelEditor.h"
#include "SWebBrowser.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "PropertyEditorModule.h"
#include "EdGraphUtilities.h"

#include "WebAsset.h"
#include "WebAssetDetails.h"
#include "WebAssetActions.h"
#include "EditorExtensionCommands.h"
#include "WebAssetSettings.h"
#include "WebAssetPinFactory.h"

#define LOCTEXT_NAMESPACE "FEditorExtensionPluginModule"

void FEditorExtensionPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	RegisterWebAssetActions();
	RegisterToolbarExtension();
	RegisterMenuExtension();
	RegisterSettings();
	RegisterDetailsCustomizations();
	RegisterConsoleCommand();
	RegisterPinFactory();
}

void FEditorExtensionPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UnregisterWebAssetActions();
	UnregisterToolbarExtension();
	UnregisterMenuExtension();
	UnregisterSettings();
	UnregisterDetailsCustomizations();
	UnregisterConsoleCommand();
	UnregisterPinFactory();
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

void FEditorExtensionPluginModule::RegisterToolbarExtension()
{
	FEditorExtensionCommands::Register();

	TSharedPtr<FUICommandList> CommandList = MakeShareable(new FUICommandList());
	CommandList->MapAction(FEditorExtensionCommands::Get().OpenWindowCommand,
		FExecuteAction::CreateRaw(this, &FEditorExtensionPluginModule::OpenBrowserWindow),
		FCanExecuteAction());

	ToolbarExtender = MakeShareable(new FExtender());
	ToolbarExtension = ToolbarExtender->AddToolBarExtension("Content", EExtensionHook::After, CommandList, 
		FToolBarExtensionDelegate::CreateRaw(this,
		&FEditorExtensionPluginModule::AddToolbarExtension));

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}

void FEditorExtensionPluginModule::UnregisterToolbarExtension()
{
	ToolbarExtender->RemoveExtension(ToolbarExtension.ToSharedRef());
	ToolbarExtension.Reset();
	ToolbarExtender.Reset();
}

void FEditorExtensionPluginModule::AddToolbarExtension(FToolBarBuilder &Builder)
{
	FSlateIcon IconBrush = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tutorials");

	Builder.AddToolBarButton(FEditorExtensionCommands::Get()
		.OpenWindowCommand, NAME_None, FText::FromString("My Tutorials"),
		FText::FromString("Need help? Click here"),
		IconBrush, NAME_None);
}

void FEditorExtensionPluginModule::RegisterMenuExtension()
{
	FEditorExtensionCommands::Register();

	TSharedPtr<FUICommandList> CommandList = MakeShareable(new FUICommandList());
	CommandList->MapAction(FEditorExtensionCommands::Get().OpenWindowCommand,
		FExecuteAction::CreateRaw(this, &FEditorExtensionPluginModule::OpenBrowserWindow),
		FCanExecuteAction());

	MenuExtender = MakeShareable(new FExtender());
	MenuExtension = MenuExtender->AddMenuExtension("Tutorials", EExtensionHook::After, CommandList,
		FMenuExtensionDelegate::CreateRaw(this,
		&FEditorExtensionPluginModule::AddMenuExtension));

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void FEditorExtensionPluginModule::UnregisterMenuExtension()
{
	MenuExtender->RemoveExtension(MenuExtension.ToSharedRef());
	MenuExtender.Reset();
	MenuExtender.Reset();
}

void FEditorExtensionPluginModule::AddMenuExtension(FMenuBuilder & Builder)
{
	FSlateIcon IconBrush = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tutorials");

	Builder.AddMenuEntry(FEditorExtensionCommands::Get()
		.OpenWindowCommand, NAME_None, FText::FromString("Raywenderlich"),
		FText::FromString("Go to raywenderlich.com"),
		IconBrush, NAME_None);
}

void FEditorExtensionPluginModule::OpenBrowserWindow()
{
	auto WebBrowser = SNew(SWebBrowser)
		.InitialURL("https://www.raywenderlich.com/");

	FVector2D WindowSize = GetMutableDefault<UWebAssetSettings>()->WindowSize;

	TSharedRef<SWindow> Window = SNew(SWindow)
		.Title(FText::FromString(TEXT("New window")))
		.ClientSize(WindowSize)
		.SupportsMaximize(false)
		.SupportsMinimize(false)
		[
			WebBrowser
		];

	IMainFrameModule& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

	if (MainFrameModule.GetParentWindow().IsValid())
	{
		FSlateApplication::Get().AddWindowAsNativeChild(Window, MainFrameModule.GetParentWindow().ToSharedRef());
	}
	else
	{
		FSlateApplication::Get().AddWindow(Window);
	}
}

void FEditorExtensionPluginModule::RegisterSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		SettingsContainer->DescribeCategory("WebAsset Extension Settings",
			LOCTEXT("WASettings", "Web Asset Settings"),
			LOCTEXT("Description", "Configure the Web Asset extension"));

		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "EditorExtension", "General",
			LOCTEXT("WASettings", "Settings"),
			LOCTEXT("Description", "Configure the Web Asset extension"),
			GetMutableDefault<UWebAssetSettings>()
		);
	}
}

void FEditorExtensionPluginModule::UnregisterSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Settings", "General");
	}
}

void FEditorExtensionPluginModule::RegisterDetailsCustomizations()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.RegisterCustomClassLayout(UWebAsset::StaticClass()->GetFName(),
				FOnGetDetailCustomizationInstance::CreateStatic(&FWebAssetDetails::MakeInstance));
}

void FEditorExtensionPluginModule::UnregisterDetailsCustomizations()
{
	FPropertyEditorModule& PropertyModule =FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.UnregisterCustomClassLayout(UWebAsset::StaticClass()->GetFName());
}

void FEditorExtensionPluginModule::RegisterConsoleCommand()
{
	DisplayWindowCommand = IConsoleManager::Get().RegisterConsoleCommand(TEXT("DisplayBrowserWindow"), TEXT("Display a web page"),
		FConsoleCommandDelegate::CreateRaw(this, &FEditorExtensionPluginModule::OpenBrowserWindow));
}

void FEditorExtensionPluginModule::UnregisterConsoleCommand()
{
	if(DisplayWindowCommand)
	{
		IConsoleManager::Get().UnregisterConsoleObject(DisplayWindowCommand);
		DisplayWindowCommand = nullptr;
	}
}

void FEditorExtensionPluginModule::RegisterPinFactory()
{
	PinFactory = MakeShareable(new FWebAssetPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(PinFactory);
}

void FEditorExtensionPluginModule::UnregisterPinFactory()
{
	FEdGraphUtilities::UnregisterVisualPinFactory(PinFactory);
	PinFactory.Reset();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorExtensionPluginModule, EditorExtensionPlugin)