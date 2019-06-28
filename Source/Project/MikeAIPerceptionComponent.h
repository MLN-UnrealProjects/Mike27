// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "MikeAIPerceptionComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), Blueprintable)
/**
 * Custom AIPerception that allows to dynamically modify its senses
 */
class PROJECT_API UMikeAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

		UMikeAIPerceptionComponent();
private:
	UAISenseConfig_Hearing* Config_Hearing = nullptr;
	UAISenseConfig_Sight* Config_Sight = nullptr;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config|AIPerception")
	/**
 * Returns the requested AISense Config (if there is one).
 * @param SenseClass - Type of AISense class to look for
 * @return The AISense Config found (nullptr if not found)
 */
	UAISenseConfig* GetPerceptionSenseConfig(const TSubclassOf<UAISense>& SenseClass);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config|AIPerception")
	/**
* Returns the requested AISense Config Hearing(if there is one).
* @return The AISense Config Hearing found (nullptr if not found)
*/
	UAISenseConfig_Hearing* GetPerceptionSenseHearing();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config|AIPerception")
	/**
* Returns the requested AISense Sight Hearing(if there is one).
* @return The AISense Config Sight found (nullptr if not found)
*/
	UAISenseConfig_Sight* GetPerceptionSenseSight();
	UFUNCTION(BlueprintCallable, Category = "Config|AIPerception")
	/**
* Sets the given Sight range to the Sight sense
* @param SightRadius - The sight radius amount to set
* @return True if operation was successfully completed
*/
	bool SetSightRange(const float SightRadius);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config|AIPerception")
	/**
* Returns the requested AISense Sight Range.
* @return The AISense Config Sight range, INVALID_RANGE if the operation did not complete successfully
*/
	float GetSightRange() const;
	UFUNCTION(BlueprintCallable, Category = "Config|AIPerception")
	/**
* Sets the given Hearing range to the Hear sense
* @param HearRange - The hearing radius amount to set
* @return True if operation was successfully completed
*/
	bool SetHearRange(const float HearRange);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config|AIPerception")
	/**
* Returns the requested AISense Hear Range.
* @return The AISense Config Hear range, INVALID_RANGE if the operation did not complete successfully
*/
	float GetHearRange() const;
	UFUNCTION(BlueprintCallable, Category = "Config|AIPerception")
	/**
* Sets the given Sight angle vision to the Sight sense
* @param Angle - The hearing angle amount to set
* @return True if operation was successfully completed
*/
	bool SetPeripheralAngleVision(const float Angle);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config|AIPerception")
	/**
* Returns the requested AISense Sight Angle vision.
* @return The AISense Config Sight Angle vision, INVALID_RANGE if the operation did not complete successfully
*/
	float GetPeripheralAngleVision() const;
};
