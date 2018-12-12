// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WebAssetSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig)
class UWebAssetSettings : public UObject
{
	GENERATED_BODY()

public:
	UWebAssetSettings() {};

	UPROPERTY(EditAnywhere, config, Category = Window)
	FVector2D WindowSize;
};
