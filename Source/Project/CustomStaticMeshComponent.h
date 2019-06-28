// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "CustomStaticMeshComponent.generated.h"

UCLASS(ClassGroup = Rendering, meta = (BlueprintSpawnableComponent), Blueprintable)
/**
 * Custom Static mesh component to allow bp components to derive from UStaticMeshComponent
 */
class PROJECT_API UCustomStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
};
