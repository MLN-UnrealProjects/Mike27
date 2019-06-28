// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "CustomBoxComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), Blueprintable)
/**
 * Custom Box component to allow bp components to derive from UBoxComponent
 */
class PROJECT_API UCustomBoxComponent : public UBoxComponent
{
	GENERATED_BODY()
	
};
