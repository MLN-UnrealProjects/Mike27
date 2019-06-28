// Fill out your copyright notice in the Description page of Project Settings.

#include "Mike27BlueprintFunctionLibrary.h"

#include "TimerManager.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Sound/SoundBase.h"

float UMike27BlueprintFunctionLibrary::RadToDeg = 180.f / PI;
float UMike27BlueprintFunctionLibrary::DegToRad = PI / 180.f;
bool UMike27BlueprintFunctionLibrary::bDebugEnabled = false;
bool UMike27BlueprintFunctionLibrary::b3DPathfindingEnabled = false;

bool UMike27BlueprintFunctionLibrary::GetActorBoundsCenter(const AActor* const Actor, const bool bOnlyCollidingComponents, FVector& Center, FVector& Extents)
{
	if (Actor == nullptr)
	{
		return false;
	}
	Actor->GetActorBounds(bOnlyCollidingComponents, Center, Extents);
	return true;
}
bool UMike27BlueprintFunctionLibrary::Is3DPathfindingEnabled()
{
	return UMike27BlueprintFunctionLibrary::b3DPathfindingEnabled;
}
void UMike27BlueprintFunctionLibrary::Set3DPathfindingEnabled(const bool bEnabled)
{
	UMike27BlueprintFunctionLibrary::b3DPathfindingEnabled = bEnabled;
}
bool UMike27BlueprintFunctionLibrary::IsDebugEnabled()
{
	return UMike27BlueprintFunctionLibrary::bDebugEnabled;
}
void UMike27BlueprintFunctionLibrary::SetDebugEnabled(const bool bEnabled)
{
	UMike27BlueprintFunctionLibrary::bDebugEnabled = bEnabled;
}
float UMike27BlueprintFunctionLibrary::GetRadiansToDegreesMultiplier()
{
	return UMike27BlueprintFunctionLibrary::RadToDeg;
}
float UMike27BlueprintFunctionLibrary::GetDegreesToRadiansMultiplier()
{
	return UMike27BlueprintFunctionLibrary::DegToRad;
}
float UMike27BlueprintFunctionLibrary::GetNearClipPlane()
{
	return GNearClippingPlane;
}
void UMike27BlueprintFunctionLibrary::SetNearClipPlane(const float Value)
{
	GNearClippingPlane = Value;
}
bool UMike27BlueprintFunctionLibrary::IsTimerValid(const UObject* const WorldContextObject, const FTimerHandle& Handle, float& OutTimeLeft, float& OutTimeElapsed)
{
	const UWorld* const World = WorldContextObject->GetWorld();
	if (World == nullptr)
	{
		return false;
	}
	FTimerManager& Manager = World->GetTimerManager();
	OutTimeElapsed = Manager.GetTimerElapsed(Handle);
	OutTimeLeft = Manager.GetTimerRemaining(Handle);
	return Manager.TimerExists(Handle);
}
float UMike27BlueprintFunctionLibrary::GetAngleDegrees(const FVector& first, const FVector& second)
{
	return GetAngleRadians(first, second) * UMike27BlueprintFunctionLibrary::RadToDeg;
}
float UMike27BlueprintFunctionLibrary::GetAngleRadians(const FVector& first, const FVector& second)
{
	return FMath::Acos(FVector::DotProduct(first, second));
}
float UMike27BlueprintFunctionLibrary::FastLinearConversion(const float Value, const float OldMin, const float OldMax, const float NewMin, const float NewMax)
{
	return NewMin + (((Value - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin));
}
float UMike27BlueprintFunctionLibrary::LinearConversion(const float Value, const float OldMin, const float OldMax, const float NewMin, const float NewMax)
{
	if (FMath::IsNearlyEqual(OldMax, OldMin))
	{
		return Value;
	}
	return FastLinearConversion(Value, OldMin, OldMax, NewMin, NewMax);
}
float UMike27BlueprintFunctionLibrary::FastInverseInterpolation(const float Value, const float Min, const float Max)
{
	return (Value - Min) / (Max - Min);
}
float UMike27BlueprintFunctionLibrary::InverseInterpolation(const float Value, const float Min, const float Max)
{
	if (FMath::IsNearlyEqual(Min, Max))
	{
		return 0.f;
	}
	return FastInverseInterpolation(Value, Min, Max);
}
bool UMike27BlueprintFunctionLibrary::SimpleBlockingLineTraceSingleForObjects(const UObject* const WorldContextObject, const FVector& Start, const FVector& EndDirection, const float MaxDistance, const TArray<TEnumAsByte<EObjectTypeQuery>>& BlockingObjects, const TArray<TEnumAsByte<EObjectTypeQuery>>& ValidObjects, const bool bTraceComplex, const TArray<AActor*>& ValidIgnoreList, const TArray<AActor*>& BlockingIgnoreList, const AActor* const CommonToIgnore, FHitResult& OutHitResult)
{
	const UWorld* const World = WorldContextObject->GetWorld();
	if (World == nullptr)
	{
		return false;
	}

	const FVector& End = Start + EndDirection * MaxDistance;

	FCollisionQueryParams BlockingParams(FCollisionQueryParams::DefaultQueryParam);
	FCollisionQueryParams ValidParams(FCollisionQueryParams::DefaultQueryParam);
	BlockingParams.bTraceComplex = bTraceComplex;
	ValidParams.bTraceComplex = bTraceComplex;
	BlockingParams.AddIgnoredActors(BlockingIgnoreList);
	ValidParams.AddIgnoredActors(ValidIgnoreList);
	BlockingParams.AddIgnoredActor(CommonToIgnore);
	ValidParams.AddIgnoredActor(CommonToIgnore);

	const bool BlockingResult = World->LineTraceSingleByObjectType(OutHitResult, Start, End, BlockingObjects, BlockingParams);
	if (!BlockingResult)
	{
		return World->LineTraceSingleByObjectType(OutHitResult, Start, End, ValidObjects, ValidParams);
	}

	FHitResult OutValid = FHitResult();
	const bool ValidResult = World->LineTraceSingleByObjectType(OutValid, Start, End, ValidObjects, ValidParams);
	if (ValidResult && OutValid.Distance <= OutHitResult.Distance)
	{
		OutHitResult = OutValid;
		return true;
	}

	return false;
}
bool UMike27BlueprintFunctionLibrary::SimpleBlockingDoubleLineTraceSingleForObjects(const UObject* const WorldContextObject, const FVector& AimStart, const FVector& EffectiveStart, const FVector& AimEndDirection, const float MaxDistance, const TArray<TEnumAsByte<EObjectTypeQuery>>& BlockingObjects, const TArray<TEnumAsByte<EObjectTypeQuery>>& ValidObjects, const bool bTraceComplex, const TArray<AActor*>& ValidIgnoreList, const TArray<AActor*>& BlockingIgnoreList, const AActor* const CommonToIgnore, FHitResult& OutHitResult)
{
	FVector SecondEndDirection;
	FHitResult AimHit = FHitResult();
	if (SimpleBlockingLineTraceSingleForObjects(WorldContextObject, AimStart, AimEndDirection, MaxDistance, BlockingObjects, ValidObjects, bTraceComplex, ValidIgnoreList, BlockingIgnoreList, CommonToIgnore, AimHit))
	{
		SecondEndDirection = (AimHit.Location - EffectiveStart).GetSafeNormal();
	}
	else
	{
		SecondEndDirection = ((AimStart + (AimEndDirection * MaxDistance)) - EffectiveStart).GetSafeNormal();
	}
	return SimpleBlockingLineTraceSingleForObjects(WorldContextObject, EffectiveStart, SecondEndDirection, MaxDistance, BlockingObjects, ValidObjects, bTraceComplex, ValidIgnoreList, BlockingIgnoreList, CommonToIgnore, OutHitResult);
}
float UMike27BlueprintFunctionLibrary::IncrementalValue(const float Value, const float MultiplierIncrement, const float Alpha = 1.f)
{
	return Value + (Value * MultiplierIncrement * Alpha);
}
float UMike27BlueprintFunctionLibrary::GetMaxAbsoluteElement(const FVector& Vector)
{
	return Vector.GetAbsMax();
}
FRotator UMike27BlueprintFunctionLibrary::ClampAngles(const FRotator& Value, const FRotator& Min, const FRotator& Max)
{
	return FRotator(FMath::ClampAngle(Value.GetComponentForAxis(EAxis::Type::Y), Min.GetComponentForAxis(EAxis::Type::Y), Max.GetComponentForAxis(EAxis::Type::Y)), FMath::ClampAngle(Value.GetComponentForAxis(EAxis::Type::Z), Min.GetComponentForAxis(EAxis::Type::Z), Max.GetComponentForAxis(EAxis::Type::Z)), FMath::ClampAngle(Value.GetComponentForAxis(EAxis::Type::X), Min.GetComponentForAxis(EAxis::Type::X), Max.GetComponentForAxis(EAxis::Type::X)));
}
int32 UMike27BlueprintFunctionLibrary::CircularClamp(const int32 Value, const int32 Min, const int32 Max)
{
	if (Value > Max)
	{
		return Min;
	}
	if (Value < Min)
	{
		return Max;
	}
	return Value;
}
bool UMike27BlueprintFunctionLibrary::ExclusiveRandomInRange(const int32 ExcludedValue, const int32 Min, const int32 Max, int32& OutRandomValue)
{
	if (Min >= Max)
	{
		OutRandomValue = FMath::RandRange(Min, Max);
		return false;
	}

	do
	{
		OutRandomValue = FMath::RandRange(Min, Max);
	} while (OutRandomValue == ExcludedValue);

	return true;
}
bool UMike27BlueprintFunctionLibrary::IsMovingForward(const float ForwardAngleThreshold, const float RightAngleThreshold, const FVector& Forward, const FVector& Right, const FVector& Velocity, float& OutForwardAngle, float& OutRightAngle, bool& bOutIsMovingRight)
{
	const FVector& VelocityDirection(Velocity.GetSafeNormal());
	OutRightAngle = GetAngleDegrees(Right, VelocityDirection);
	OutForwardAngle = GetAngleDegrees(Forward, VelocityDirection);
	bOutIsMovingRight = RightAngleThreshold > OutRightAngle;
	return ForwardAngleThreshold > OutForwardAngle;
}
bool UMike27BlueprintFunctionLibrary::IsMovingForwardXY(const float ForwardAngleThreshold, const float RightAngleThreshold, const FVector& Forward, const FVector& Right, const FVector& Velocity, float& OutForwardAngle, float& OutRightAngle, bool& bOutIsMovingRight)
{
	const float DefaultValue = 0.f;
	return IsMovingForward(ForwardAngleThreshold, RightAngleThreshold, FVector(Forward.X, Forward.Y, DefaultValue).GetSafeNormal(), FVector(Right.X, Right.Y, DefaultValue).GetSafeNormal(), FVector(Velocity.X, Velocity.Y, DefaultValue), OutForwardAngle, OutRightAngle, bOutIsMovingRight);
}
bool UMike27BlueprintFunctionLibrary::IsPhysicActive(const UPrimitiveComponent* const Target, const FName& BoneName)
{
	return Target != nullptr && Target->Mobility == EComponentMobility::Type::Movable && Target->IsSimulatingPhysics(BoneName);
}
void UMike27BlueprintFunctionLibrary::PlaySound(UObject* const WorldContextObject, UAudioComponent* const Audio, USoundBase* const Sound, const float StartTime, const bool bPerformNoise, const FVector& NoiseWorldLocation, const float Loudness, AActor* const Instigator, const float MaxRange, const FName& Tag)
{
	if (Audio != nullptr)
	{
		Audio->SetSound(Sound);
		Audio->Play(StartTime);
	}
	if (!bPerformNoise)
	{
		return;
	}
	UAISense_Hearing::ReportNoiseEvent(WorldContextObject, NoiseWorldLocation, Loudness, Instigator, MaxRange, Tag);
}