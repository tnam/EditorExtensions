// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "WebAssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class UWebAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	UWebAssetFactory();
	
	UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
