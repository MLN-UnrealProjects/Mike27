// Fill out your copyright notice in the Description page of Project Settings.

#include "PlaySoundData.h"
#include "Sound/SoundBase.h"
UPlaySoundData::UPlaySoundData()
{
	Sound = nullptr;
	StartTime = 0.f;
	bPerformNoise = false;
	Loudness = 1.f;
	MaxRange = 0.f;
	Tag = NAME_None;
}