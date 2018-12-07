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

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WebAsset")
	FString Payload;
	
};
