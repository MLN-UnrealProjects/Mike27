// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "PlaySoundDataFactory.generated.h"

/**
 * 
 */
UCLASS()
class MIKE27_API UPlaySoundDataFactory : public UFactory
{
	GENERATED_BODY()
public:
	UPlaySoundDataFactory();
	UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn);
	uint32 GetMenuCategories() const override;
	FText GetDisplayName() const override;
};
