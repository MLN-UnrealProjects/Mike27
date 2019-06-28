// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MikeBlueprintFunctionLibrary.generated.h"
/**
 *
 */
struct FTimerHandle;
class UAudioComponent;
UCLASS()
/**
 * Library for Mike project Utility
 */
class PROJECT_API UMikeBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
private:
	static float RadToDeg;
	static float DegToRad;
	static bool bDebugEnabled;
	static bool b3DPathfindingEnabled;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Collision")
		/**
 * Returns the bounding box of all components that make up this Actor (excluding ChildActorComponents).
 * @param	Actor	Actor to check
 * @param	bOnlyCollidingComponents	If true, will only return the bounding box for components with collision enabled.
 * @param	Center	The bounding box center world location
 * @param	Extents	The bounding box extents
 * @return	True if operation was succesfull, false otherwise
 */
	static bool GetActorBoundsCenter(const AActor* const Actor, const bool bOnlyCollidingComponents, FVector& Center, FVector& Extents);
	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Global")
	/**
* Returns true if 3DPathfinding is enabled
*/
	static bool Is3DPathfindingEnabled();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Config|Global")
	/**
* Sets the current 3DPathfinding enabled state
* @param bEnabled New 3DPathfinding enabled state
*/
	static void Set3DPathfindingEnabled(const bool bEnabled);
	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Global")
	/**
* Returns true if Debug is enabled
*/
	static bool IsDebugEnabled();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Config|Global")
	/**
* Sets the current Debug enabled state
* @param bEnabled New Debug enabled state
*/
	static void SetDebugEnabled(const bool bEnabled);
	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Global")
	/**
* Gets the multiplier used to convert angles from Radians to Degrees
*/
	static float GetRadiansToDegreesMultiplier();
	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Global")
	/**
* Gets the multiplier used to convert angles from Degrees to Radians
*/
	static float GetDegreesToRadiansMultiplier();
	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Global")
	/**
* Gets the near clip plane value
*/
	static float GetNearClipPlane();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Config|Global")
	/**
* Modifies the near clip plane value
* @param	Value					New near clip plane value to set
*/
	static void SetNearClipPlane(const float Value);
	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, meta = (WorldContext = WorldContextObject), Category = "Config|Timer")
	/**
* Interrogates the given handler about its validity
* @param	WorldContextObject				World context object
* @param	Handle					The Timer handle ref to check
* @param	OutTimeLeft					The amount of seconds left before the timer runs out
* @param	OutTimeElapsed					The amount of seconds elapsed since the timer start
* @return	True if a timer by the given handler exists
*/
	static bool IsTimerValid(const UObject* const WorldContextObject, const FTimerHandle& Handle, float& OutTimeLeft, float& OutTimeElapsed);
	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Math")
	/**
* Returns the angle (Degrees) formed by the given two vectors
* @param	first					First vector to consider
* @param	second					Second vector to consider
* @return The resulting angle (Degrees)
*/
	static float GetAngleDegrees(const FVector& first, const FVector& second);
	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Math")
	/**
* Returns the angle (Radians) formed by the given two vectors
* @param	first					First vector to consider
* @param	second					Second vector to consider
* @return The resulting angle (Radians)
*/
	static float GetAngleRadians(const FVector& first, const FVector& second);
	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Math")
	/**
* Returns the linear conversion of the given value from an old range to a new range
* @param	Value					Value to convert
* @param	OldMin					Original range min value
* @param	OldMax					Original range max value
* @param	NewMin					Target range min value
* @param	NewMax					Target range max value
* @return		Conversion result.
* @warning If oldmin is equal to oldmax the returned amount will always be equal to Value
*/
	static float LinearConversion(const float Value, const float OldMin, const float OldMax, const float NewMin, const float NewMax);
	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Math")
	/**
* Returns the linear conversion of the given value from an old range to a new range.
* @param	Value					Value to convert
* @param	OldMin					Original range min value
* @param	OldMax					Original range max value
* @param	NewMin					Target range min value
* @param	NewMax					Target range max value
* @return		Conversion result.
* @warning A division by zero will occur if OldMin and OldMax are equal
*/
	static float FastLinearConversion(const float Value, const float OldMin, const float OldMax, const float NewMin, const float NewMax);

	UFUNCTION(BlueprintCallable, CallInEditor, meta = (WorldContext = WorldContextObject), Category = "Config|Linetrace")
	/**
* Execute a double physic linetrace (one blocking and one valid)
* @param	WorldContextObject					Context
* @param	Start					Start location for both linetraces
* @param	EndDirection					Valid linetrace direction
* @param	MaxDistance					Max distance for a valid hit
* @param	BlockingObjects					Objects queried for the blocking linetrace
* @param	ValidObjects					Objects queried for the valid linetrace
* @param	bTraceComplex					Whetever both linetraces should track complex collisions
* @param	ValidIgnoreList					Actors ignored for the valid linetrace
* @param	BlockingIgnoreList				Actors ignored for the blocking linetrace
* @param	CommonToIgnore					Common actor to be ignored by both linetraces (can be used to ignore self)
* @param	OutHitResult						The result of the linetraces (valid linetrace will be prioritized)
* @return		True if a valid objects was hit
*/
	static bool SimpleBlockingLineTraceSingleForObjects(const UObject* const WorldContextObject, const FVector& Start, const FVector& EndDirection, const float MaxDistance, const TArray<TEnumAsByte<EObjectTypeQuery>>& BlockingObjects, const TArray<TEnumAsByte<EObjectTypeQuery>>& ValidObjects, const bool bTraceComplex, const TArray<AActor*>& ValidIgnoreList, const TArray<AActor*>& BlockingIgnoreList, const AActor* const CommonToIgnore, FHitResult& OutHitResult);

	UFUNCTION(BlueprintCallable, CallInEditor, meta = (WorldContext = WorldContextObject), Category = "Config|Linetrace")
	/**
* Execute two double physic linetraces (one for aiming and one valid)
* @param	WorldContextObject					Context
* @param	AimStart						Start location for aiming linetraces
* @param	EffectiveStart					Start location for valid linetraces
* @param	AimEndDirection					Aiming linetraces direction
* @param	MaxDistance						Max distance for a valid hit
* @param	BlockingObjects					Objects queried for the blocking linetraces
* @param	ValidObjects					Objects queried for the valid linetraces
* @param	bTraceComplex					Whetever all linetraces should track complex collisions
* @param	ValidIgnoreList					Actors ignored for the valid linetraces
* @param	BlockingIgnoreList				Actors ignored for the blocking linetraces
* @param	CommonToIgnore					Common actor to be ignored by all linetraces (can be used to ignore self)
* @param	OutHitResult						The result of the valid linetraces (valid linetrace will be prioritized)
* @return		True if a valid objects was hit
*/
	static bool SimpleBlockingDoubleLineTraceSingleForObjects(const UObject* const WorldContextObject, const FVector& AimStart, const FVector& EffectiveStart, const FVector& AimEndDirection, const float MaxDistance, const TArray<TEnumAsByte<EObjectTypeQuery>>& BlockingObjects, const TArray<TEnumAsByte<EObjectTypeQuery>>& ValidObjects, const bool bTraceComplex, const TArray<AActor*>& ValidIgnoreList, const TArray<AActor*>& BlockingIgnoreList, const AActor* const CommonToIgnore, FHitResult& OutHitResult);

	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Math")
	/**
* Increments the given value by an additive multiplier and a given alpha percentage
* @param	Value					Value to increment
* @param	MultiplierIncrement		Additive multiplier
* @param	Alpha					Alpha percentage
* @return		Incremented value
*/
	static float IncrementalValue(const float Value, const float MultiplierIncrement, const float Alpha);

	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Math")
	/**
* Finds the highest absolute element value of a given vector
* @param	Vector					Vector to check
* @return		Highest absolute element
*/
	static float GetMaxAbsoluteElement(const FVector& Vector);

	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Math")
	/**
* Determines the percentage at which the given value is in the given range
* @param	Value				Value to test
* @param	Min					Min value
* @param	Max					Max value
* @return		Percentage 
* @warning A division by 0 will occur if Min is equal to Max.
*/
	static float FastInverseInterpolation(const float Value, const float Min, const float Max);

	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Math")
	/**
* Determines the percentage at which the given value is in the given range
* @param	Value				Value to test
* @param	Min					Min value
* @param	Max					Max value
* @return		Percentage
* @warning If Min is equal to Max 0 will always be returned
*/
	static float InverseInterpolation(const float Value, const float Min, const float Max);
	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Math")
	/**
* Clamps the given rotator in a given range. Will clamp angles to nearest boundary.
* @param	Value				Rotator to clamp
* @param	Min					Min angle
* @param	Max					Max angle
* @return		Clamped rotator
*/
	static FRotator ClampAngles(const FRotator& Value, const FRotator& Min, const FRotator& Max);

	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Math")
	/**
* Clamps the given int in a given range. Will clamp values in a circular looping way.
* @param	Value				Value to clamp
* @param	Min					Min value
* @param	Max					Max value
* @return		Clamped value
*/
	static int32 CircularClamp(const int32 Value, const int32 Min, const int32 Max);

	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Math")
	/**
* Tries to get a random value in a given range that is not equal to the given excluded value
* @param	ExcludedValue		The excluded value
* @param	Min					Min value
* @param	Max					Max value
* @param	OutRandomValue			The output random value found
* @return		False if it was either not possible to return a valid value or Min is >= Max
*/
	static bool ExclusiveRandomInRange(const int32 ExcludedValue, const int32 Min, const int32 Max, int32& OutRandomValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Math")
	/**
* Determines if the given velocity is moving forward given the directions, also calculates other utility values.
* @param	ForwardAngleThreshold		Minimum angle degrees to consider the velocity as 'moving forward'
* @param	RightAngleThreshold			Minimum angle degrees to consider the velocity as 'moving right'
* @param	Forward						Forward direction
* @param	Right						Right direction
* @param	Velocity					Velocity to check
* @param	OutForwardAngle				The output angle degrees between velocity and forward direction
* @param	OutRightAngle					The output angle degrees between velocity and right direction
* @param	bOutIsMovingRight				True if velocity can be considered as 'moving right'
* @return		True if velocity can be considered as 'moving forward'
*/
	static bool IsMovingForward(const float ForwardAngleThreshold, const float RightAngleThreshold, const FVector& Forward, const FVector& Right, const FVector& Velocity, float& OutForwardAngle, float& OutRightAngle, bool& bOutIsMovingRight);

	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Math")
	/**
* Determines if the given velocity is moving forward given the directions, also calculates other utility values. The Z axis is not considered
* @param	ForwardAngleThreshold		Minimum angle degrees to consider the velocity as 'moving forward'
* @param	RightAngleThreshold			Minimum angle degrees to consider the velocity as 'moving right'
* @param	Forward						Forward direction
* @param	Right						Right direction
* @param	Velocity					Velocity to check
* @param	OutForwardAngle				The output angle degrees between velocity and forward direction
* @param	OutRightAngle					The output angle degrees between velocity and right direction
* @param	bOutIsMovingRight				True if velocity can be considered as 'moving right'
* @return		True if velocity can be considered as 'moving forward'
*/
	static bool IsMovingForwardXY(const float ForwardAngleThreshold, const float RightAngleThreshold, const FVector& Forward, const FVector& Right, const FVector& Velocity, float& OutForwardAngle, float& OutRightAngle, bool& bOutIsMovingRight);

	UFUNCTION(BlueprintCallable, BlueprintPure, CallInEditor, Category = "Config|Physics")
	/**
* Controls if the given Target is a Physic object
* @param	Target		The Target to control
* @param	BoneName	The bone name to control
* @return		True if Target is a Physic object, false otherwise
*/
	static bool IsPhysicActive(const UPrimitiveComponent* const Target, const FName& BoneName = NAME_None);

	UFUNCTION(BlueprintCallable, CallInEditor, meta = (WorldContext = WorldContextObject), Category = "Config|Audio")
	/**
* Plays a sound and reports a noise given some parameters
* @param	WorldContextObject		Contex
* @param	Audio	The audio component used for the sound (if null no sound will be performed)
* @param	Sound	The sound to play
* @param	StartTime	The sound start time
* @param	bPerformNoise	If true a report noise event will be triggered, if false no event will be triggered
* @param	NoiseWorldLocation	World location for the noise event
* @param	Loudness	Loudness for the noise event
* @param	Instigator	Instigator of the noise event
* @param	MaxRange	MaxRange for the noise event
* @param	Tag	Tag applied to the noise event
*/
	static void PlaySound(UObject* const WorldContextObject, UAudioComponent* const Audio, USoundBase* const Sound, const float StartTime, const bool bPerformNoise, const FVector& NoiseWorldLocation, const float Loudness = 1.f, AActor* const Instigator = nullptr, const float MaxRange = 0.f, const FName& Tag = NAME_None);
};
