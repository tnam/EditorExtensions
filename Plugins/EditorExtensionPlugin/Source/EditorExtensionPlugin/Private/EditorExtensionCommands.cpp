// Fill out your copyright notice in the Description page of Project Settings.

#include "EditorExtensionCommands.h"
#include "Commands.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "EditorExtensionCommands"

FEditorExtensionCommands::FEditorExtensionCommands()
	:TCommands<FEditorExtensionCommands>(
		FName(TEXT("EditorExtensionCommands")),
		FText::FromString("Editor Commands"), NAME_None,
		FEditorStyle::GetStyleSetName()
		)
{
}

void FEditorExtensionCommands::RegisterCommands()
{
	UI_COMMAND(OpenWindowCommand, "OpenBrowser", "Open browser command", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
