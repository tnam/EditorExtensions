// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WebAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class EDITOREXTENSIONPLUGIN_API UWebAsset : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "WebAsset")
	FString Source;
	
public:
	UFUNCTION(BlueprintPure, Category = WebAsset)
	FString& GetSource() { return Source; }

	UFUNCTION(BlueprintCallable, Category = WebAsset)
	void AddDoctype();

	friend class FWebAssetDetails;
};
