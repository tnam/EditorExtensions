// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EdGraphUtilities.h"
#include "WebAsset.h"
#include "SWebAssetGraphPin.h"

class FWebAssetPinFactory : public FGraphPanelPinFactory
{
public:

	TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* Pin) const override
	{
		if (Pin->PinType.PinSubCategoryObject == UWebAsset::StaticClass())
		{
			return SNew(SWebAssetGraphPin, Pin);
		}
		else
		{
			return nullptr;
		}
	};
};
