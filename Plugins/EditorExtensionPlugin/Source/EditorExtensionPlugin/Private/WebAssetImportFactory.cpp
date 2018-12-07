// Fill out your copyright notice in the Description page of Project Settings.

#include "WebAssetImportFactory.h"
#include "WebAsset.h"
#include "Misc/FileHelper.h"

UWebAssetImportFactory::UWebAssetImportFactory()
	: Super()
{
	SupportedClass = UWebAsset::StaticClass();
	bCreateNew = false;
	bEditorImport = true;

	Formats.Add(TEXT("html;Hyper Text Markup Language"));
	Formats.Add(TEXT("htm;Hyper Text Markup Language"));
}

UObject* UWebAssetImportFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	bOutOperationCanceled = false;

	UWebAsset* WebAsset = nullptr;
	FString Payload;

	if (FFileHelper::LoadFileToString(Payload, *Filename))
	{
		WebAsset = NewObject<UWebAsset>(InParent, InClass, InName, Flags);
		WebAsset->Payload = Payload;
	}

	return WebAsset;
}
