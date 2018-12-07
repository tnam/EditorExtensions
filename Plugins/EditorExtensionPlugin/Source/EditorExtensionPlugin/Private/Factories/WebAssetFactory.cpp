// Fill out your copyright notice in the Description page of Project Settings.

#include "WebAssetFactory.h"
#include "WebAsset.h"

UWebAssetFactory::UWebAssetFactory()
	: Super()
{
	SupportedClass = UWebAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UWebAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UWebAsset>(InParent, InClass, InName, Flags);
}
