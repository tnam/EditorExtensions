// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Commands.h"


/**
*
*/
class FEditorExtensionCommands : public TCommands<FEditorExtensionCommands>
{
public:
	FEditorExtensionCommands();

	void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> OpenWindowCommand;
};