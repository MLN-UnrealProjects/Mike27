// Fill out your copyright notice in the Description page of Project Settings.

#include "GuardAIController.h"

AGuardAIController::AGuardAIController(const FObjectInitializer& init)
	: AAIController(/*init.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent"))*/)
{
	MikePerception = init.CreateDefaultSubobject<UMikeAIPerceptionComponent>(this, TEXT("MikePerception"));
	if (MikePerception != nullptr) 
	{
		MikePerception->bEditableWhenInherited = true;
	}
}