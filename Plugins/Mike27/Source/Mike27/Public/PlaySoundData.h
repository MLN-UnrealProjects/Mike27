// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlaySoundData.generated.h"

class USoundBase;
/**
 * 
 */
UCLASS()
class MIKE27_API UPlaySoundData : public UObject
{
	GENERATED_BODY()
public:
	UPlaySoundData();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	/* The sound to play
	*/
	TSoftObjectPtr<USoundBase> Sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	/* The sound start time
	*/
	float StartTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	/* If true a report noise event will be triggered, if false no event will be triggered
	*/
	bool bPerformNoise;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	/* Loudness for the noise event
	*/
	float Loudness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	/* MaxRange for the noise event
	*/
	float MaxRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	/* Tag applied to the noise event
	*/
	FName Tag;
};
