// Fill out your copyright notice in the Description page of Project Settings.

#include "WebAssetDetails.h"

#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "SWebBrowser.h"
#include "STextBlock.h"

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
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text((FText::FromString("Preview")))					
				]
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				[
					WebBrowser
				]
			]
		];

}

TSharedRef<IDetailCustomization> FWebAssetDetails::MakeInstance()
{
	return MakeShareable(new FWebAssetDetails);
}