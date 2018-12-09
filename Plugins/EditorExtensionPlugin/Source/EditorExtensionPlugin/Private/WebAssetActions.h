// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * 
 */
class FWebAssetActions : public FAssetTypeActions_Base
{
public:

	FWebAssetActions() {};

	// IAssetTypeActions interface
	bool HasActions(const TArray<UObject*>& InObjects) const override;

	void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
	FText GetName() const override;
	FColor GetTypeColor() const override;
	UClass* GetSupportedClass() const override;
	uint32 GetCategories() override;
	
	// End of IAssetTypeActions interface

private:

	void OnContextMenuClicked(TArray<TWeakObjectPtr<class UWebAsset>> Objects);

private:
	EAssetTypeCategories::Type MyAssetCategory;
};
