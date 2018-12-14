// Fill out your copyright notice in the Description page of Project Settings.

#include "SWebAssetGraphPin.h"
#include "SMultiLineEditableText.h"

#include "WebAsset.h"

void SWebAssetGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InPin);
}

TSharedRef<SWidget> SWebAssetGraphPin::GetDefaultValueWidget()
{
	return SNew(SMultiLineEditableText)
		.Text(FText::FromString("Insert source here"))
		.Font(FCoreStyle::GetDefaultFontStyle("Regular", 12))
		.LineHeightPercentage(2.0f)
		.WrapTextAt(600.0f)
		.OnTextCommitted(this, &SWebAssetGraphPin::OnTextCommitted);
}

void SWebAssetGraphPin::OnTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo)
{
	UWebAsset* NewValue = NewObject<UWebAsset>();
	NewValue->GetSource() = NewText.ToString();
	GraphPinObj->GetSchema()->TrySetDefaultObject(*GraphPinObj, NewValue);
}

