// Fill out your copyright notice in the Description page of Project Settings.

#include "WebAssetActions.h"

#include "WebAsset.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Modules/ModuleManager.h"
#include "Editor/MainFrame/Public/Interfaces/IMainFrameModule.h"
#include "Framework/Application/SlateApplication.h"
#include "SWebBrowser.h"

bool FWebAssetActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return true;
}

void FWebAssetActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder & MenuBuilder)
{
	auto WebAssets = GetTypedWeakObjectPtrs<UWebAsset>(InObjects);

	MenuBuilder.AddMenuEntry(
		FText::FromString("Preview"),
		FText::FromString("Preview the selected Web Asset"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateSP(this, &FWebAssetActions::OnContextMenuClicked, WebAssets), FCanExecuteAction()
		));
}

FText FWebAssetActions::GetName() const
{
	return FText::FromString(TEXT("Web Asset"));
}

FColor FWebAssetActions::GetTypeColor() const
{
	return FColor::Blue;
}

UClass * FWebAssetActions::GetSupportedClass() const
{
	return UWebAsset::StaticClass();
}

uint32 FWebAssetActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

void FWebAssetActions::OnContextMenuClicked(TArray<TWeakObjectPtr<UWebAsset>> Objects)
{
	for (const auto& Obj : Objects)
	{
		FString Payload = Obj->GetSource();

		auto WebBrowser = SNew(SWebBrowser);
		WebBrowser->LoadString(Payload, "");

		TSharedRef<SWindow> PreviewWindow = SNew(SWindow)
			.Title(FText::FromString(TEXT("Preview window")))
			.ClientSize(FVector2D(1024, 768))
			.SupportsMaximize(false)
			.SupportsMinimize(false)
			[
				WebBrowser
			];

		IMainFrameModule& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));
		if (MainFrameModule.GetParentWindow().IsValid())
		{
			FSlateApplication::Get().AddWindowAsNativeChild
			(PreviewWindow, MainFrameModule.GetParentWindow().ToSharedRef());
		}
		else
		{
			FSlateApplication::Get().AddWindow(PreviewWindow);
		}
	}
}
