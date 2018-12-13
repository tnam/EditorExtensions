// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DetailLayoutBuilder.h"
#include "IDetailCustomization.h"

/**
 * 
 */
class FWebAssetDetails : public IDetailCustomization
{

public:

	void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	static TSharedRef<IDetailCustomization> MakeInstance();
};
