// Fill out your copyright notice in the Description page of Project Settings.

#include "MikeAIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISense_Hearing.h"
#define INVALID_RANGE -1.0f


///Costruttore da vedere, still broken///
UMikeAIPerceptionComponent::UMikeAIPerceptionComponent()
{
	Config_Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Sense"));
	if (!Config_Hearing->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("Config_Hearing isn't created!"))
	}

	Config_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Sense"));
	if (!Config_Sight->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("Config_Sight isn't created!"))
	}


#pragma region Config_Hearing
	Config_Hearing->HearingRange = 800;
	Config_Hearing->DetectionByAffiliation.bDetectEnemies = true;
	Config_Hearing->DetectionByAffiliation.bDetectFriendlies = true;
	Config_Hearing->DetectionByAffiliation.bDetectNeutrals = true;
#pragma endregion Config_Hearing

#pragma region Config_Sight
	Config_Sight->SightRadius = 1300;
	Config_Sight->LoseSightRadius = 1800;
	Config_Sight->PeripheralVisionAngleDegrees = 60;
	Config_Sight->DetectionByAffiliation.bDetectEnemies = true;
	Config_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Config_Sight->DetectionByAffiliation.bDetectNeutrals = true;
#pragma endregion Config_Sight


	this->ConfigureSense(*Config_Hearing);
	this->ConfigureSense(*Config_Sight);

	this->SetDominantSense(UAISenseConfig_Sight::StaticClass());
}
UAISenseConfig_Hearing* UMikeAIPerceptionComponent::GetPerceptionSenseHearing()
{
	const FAISenseID SenseID = UAISense::GetSenseID(UAISense_Hearing::StaticClass());
	if (!SenseID.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("AI Sense Perception ID is not valid"));
		return nullptr;
	}

	return Cast<UAISenseConfig_Hearing>(GetSenseConfig(SenseID));
}
UAISenseConfig_Sight* UMikeAIPerceptionComponent::GetPerceptionSenseSight()
{
	const FAISenseID SenseID = UAISense::GetSenseID(UAISense_Sight::StaticClass());
	if (!SenseID.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("AI Sense Perception ID is not valid"));
		return nullptr;
	}

	return Cast<UAISenseConfig_Sight>(GetSenseConfig(SenseID));
}
UAISenseConfig* UMikeAIPerceptionComponent::GetPerceptionSenseConfig(const TSubclassOf<UAISense>& SenseClass)
{
	const FAISenseID SenseID = UAISense::GetSenseID(SenseClass);
	if (!SenseID.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("AI Sense Perception ID is not valid"));
		return nullptr;
	}

	return GetSenseConfig(SenseID);
}

bool UMikeAIPerceptionComponent::SetSightRange(const float SightRadius)
{

	if (Config_Sight == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SenseConfig of SetSightRange is null"));
		return false;
	}

	//Debug
	/*UE_LOG(LogTemp, Verbose, TEXT("SetSightRange was %f %f, setting to %f %f")
		, ConfigSight->SightRadius, ConfigSight->LoseSightRadius, SightRadius, (ConfigSight->LoseSightRadius - ConfigSight->SightRadius + SightRadius));*/

	//Save distance from sight radius and lose sight radius current
	const float LoseRange = Config_Sight->LoseSightRadius - Config_Sight->SightRadius;
	Config_Sight->SightRadius = SightRadius;
	//LoseSightRadius automatically reset with the same "distance" 
	Config_Sight->LoseSightRadius = Config_Sight->SightRadius + LoseRange;

	RequestStimuliListenerUpdate();
	return true;
}

float UMikeAIPerceptionComponent::GetSightRange() const
{
	if (Config_Sight == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SenseConfig of GetSightRange is null"));
		return INVALID_RANGE;
	}
	return Config_Sight->SightRadius;
}

bool UMikeAIPerceptionComponent::SetHearRange(const float HearRange)
{
	if (Config_Hearing == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SenseConfig of SetHearRange is null"));
		return false;
	}

	Config_Hearing->HearingRange = HearRange;
	RequestStimuliListenerUpdate();
	return true;
}

float UMikeAIPerceptionComponent::GetHearRange() const
{
	if (Config_Hearing == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SenseConfig of GetHearRange is null"));
		return INVALID_RANGE;
	}
	return Config_Hearing->HearingRange;
}

bool UMikeAIPerceptionComponent::SetPeripheralAngleVision(const float Angle)
{
	if (Config_Sight == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SenseConfig of SetPeripheralAngleVision is null"));
		return false;
	}


	Config_Sight->PeripheralVisionAngleDegrees = Angle;

	RequestStimuliListenerUpdate();
	return true;
}

float UMikeAIPerceptionComponent::GetPeripheralAngleVision() const
{
	if (Config_Sight == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SenseConfig of GetPeripheralAngleVision is null"));
		return INVALID_RANGE;
	}
	return Config_Sight->PeripheralVisionAngleDegrees;
}