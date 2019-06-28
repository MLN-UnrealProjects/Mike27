// Fill out your copyright notice in the Description page of Project Settings.

#include "PlaySoundDataFactory.h"
#include "PlaySoundData.h"
#include "AssetTypeCategories.h"

UPlaySoundDataFactory::UPlaySoundDataFactory()
{
	this->SupportedClass = UPlaySoundData::StaticClass();
	this->bCreateNew = true;
}
UObject* UPlaySoundDataFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UPlaySoundData>(InParent, InClass, InName, Flags);
}

FText UPlaySoundDataFactory::GetDisplayName() const
{
	return FText::FromString(TEXT("Play Sound Data"));
}

uint32 UPlaySoundDataFactory::GetMenuCategories() const
{
	return EAssetTypeCategories::Blueprint;
}