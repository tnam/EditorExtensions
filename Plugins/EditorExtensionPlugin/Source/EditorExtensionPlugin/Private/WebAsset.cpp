// Fill out your copyright notice in the Description page of Project Settings.

#include "WebAsset.h"

void UWebAsset::AddDoctype()
{
	if(Source.StartsWith(TEXT("<!DOCTYPE")))
	{
		UE_LOG(LogTemp, Warning, TEXT("Document already contains a DOCTYPE"));
		return;
	}

	FString doctype = TEXT("<!DOCTYPE html>");
	doctype += LINE_TERMINATOR;
	Source.InsertAt(0, doctype);
}
