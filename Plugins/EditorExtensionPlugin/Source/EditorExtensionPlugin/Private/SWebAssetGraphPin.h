// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SGraphPin.h"

class SWebAssetGraphPin : public SGraphPin
{
	SLATE_BEGIN_ARGS(SWebAssetGraphPin) {}
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);

	TSharedRef<SWidget> GetDefaultValueWidget() override;

	void OnTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);
};
