// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "WebAssetImportFactory.generated.h"

/**
 * 
 */
UCLASS()
class UWebAssetImportFactory : public UFactory
{
	GENERATED_BODY()

public:
	UWebAssetImportFactory();

	UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
};
