// Fill out your copyright notice in the Description page of Project Settings.

#include "WebAssetDetails.h"

#include "IDetailsView.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "SWebBrowser.h"

void FWebAssetDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	auto Handle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UWebAsset, Payload));
	FString Payload;  
	Handle->GetValue(Payload);

	auto WebBrowser = SNew(SWebBrowser)
		.ShowControls(false)
		.ShowAddressBar(false);
	WebBrowser->LoadString(Payload, "");


	DetailBuilder.EditCategory("Preview", FText::GetEmpty(), ECategoryPriority::Important).AddCustomRow(FText::GetEmpty())
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.VAlign(VAlign_Center)
		[
			WebBrowser
		]
		];

}

TSharedRef<IDetailCustomization> FWebAssetDetails::MakeInstance()
{
	return MakeShareable(new FWebAssetDetails);
}