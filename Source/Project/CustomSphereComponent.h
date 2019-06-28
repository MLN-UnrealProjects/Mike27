// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "CustomSphereComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), Blueprintable)
/**
 * Custom Sphere component to allow bp components to derive from USphereComponent
 */
class PROJECT_API UCustomSphereComponent : public USphereComponent
{
	GENERATED_BODY()
	
};
