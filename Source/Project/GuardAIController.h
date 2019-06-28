// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MikeAIPerceptionComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "AIController.h"
#include "GuardAIController.generated.h"

UCLASS()
/**
 * Default controller class for guard type ai with crowd avoidance system and mikeperception
 */
class PROJECT_API AGuardAIController : public AAIController
{
	GENERATED_BODY()
		AGuardAIController(const FObjectInitializer& init);
public:
	/** The MikePerception relative to this controller */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config|Perception")
		UMikeAIPerceptionComponent* MikePerception = nullptr;
};
