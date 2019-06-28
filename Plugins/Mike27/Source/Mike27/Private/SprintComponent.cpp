// Fill out your copyright notice in the Description page of Project Settings.

#include "SprintComponent.h"
#include "Mike27BlueprintFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values for this component's properties
USprintComponent::USprintComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;


	SpeedMultiplierIncrement = 0.5f;
	AccelerationMultiplierIncrement = 0.5f;
	ForwardAngleTollerance = 90.f;
	OriginalAcceleration = 0.f;
	OriginalSpeed = 0.f;
	bEnabled = true;
	CharacterMovement = nullptr;
	bInitializeAtBeginPlay = true;
	// ...
}
void USprintComponent::StartSprint()
{
	if (IsEnabled() && !IsSprintActive())
	{
		SetComponentTickEnabled(true);
		if (CharacterMovement)
		{
			SetSavedMovementStats(CharacterMovement->MaxWalkSpeed, CharacterMovement->MaxAcceleration);
		}
	}
}
void USprintComponent::StopSprint()
{
	if (IsSprintActive())
	{
		SetComponentTickEnabled(false);
		SetSavedStatsToCharacter();
	}
}
void USprintComponent::Initialize(UCharacterMovementComponent* const InCharacter, const bool bInEnabled)
{
	StopSprint();
	CharacterMovement = InCharacter;
	if (CharacterMovement)
	{
		SetSavedMovementStats(CharacterMovement->MaxWalkSpeed, CharacterMovement->MaxAcceleration);
		SetEnabled(bInEnabled);
	}
}
bool USprintComponent::IsEnabled() const
{
	return bEnabled;
}
void USprintComponent::SetEnabled(const bool bInEnabled)
{
	bEnabled = bInEnabled;
	if (!bEnabled)
	{
		StopSprint();
	}
}
void USprintComponent::SetSavedStatsToCharacter() const
{
	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = OriginalSpeed;
		CharacterMovement->MaxAcceleration = OriginalAcceleration;
	}
}
void USprintComponent::SetSavedMovementStats(const float MaxWalkSpeed, const float MaxAcceleration)
{
	OriginalSpeed = MaxWalkSpeed;
	OriginalAcceleration = MaxAcceleration;
}
float USprintComponent::GetMaxAcceleration() const
{
	if (IsSprintActive() || !CharacterMovement)
	{
		return UMike27BlueprintFunctionLibrary::IncrementalValue(OriginalAcceleration, AccelerationMultiplierIncrement, 1.0f);
	}
	return UMike27BlueprintFunctionLibrary::IncrementalValue(CharacterMovement->MaxAcceleration, AccelerationMultiplierIncrement, 1.0f);
}
UCharacterMovementComponent* USprintComponent::GetCharacterMovement() const
{
	return CharacterMovement;
}
float USprintComponent::GetMaxWalkSpeed() const
{
	if (IsSprintActive() || !CharacterMovement)
	{
		return UMike27BlueprintFunctionLibrary::IncrementalValue(OriginalSpeed, SpeedMultiplierIncrement, 1.0f);
	}
	return UMike27BlueprintFunctionLibrary::IncrementalValue(CharacterMovement->MaxWalkSpeed, SpeedMultiplierIncrement, 1.0f);
}
void USprintComponent::GetSavedMovementStats(float& MaxWalkSpeed, float& MaxAcceleration) const
{
	MaxWalkSpeed = OriginalSpeed;
	MaxAcceleration = OriginalAcceleration;
}
bool USprintComponent::IsSprintActive() const
{
	return IsComponentTickEnabled();
}
// Called when the game starts
void USprintComponent::BeginPlay()
{
	Super::BeginPlay();
	if (bInitializeAtBeginPlay)
	{
		UCharacterMovementComponent* Movement = nullptr;
		const AActor* const Owner = GetOwner();
		if (Owner)
		{
			UActorComponent* const GettedComponent = Owner->GetComponentByClass(UCharacterMovementComponent::StaticClass());
			if (GettedComponent)
			{
				Movement = Cast<UCharacterMovementComponent>(GettedComponent);
			}
		}
		Initialize(Movement, true);
	}
	// ...

}
bool USprintComponent::IsMovingForward(float& OutDot) const
{
	if (!CharacterMovement)
	{
		OutDot = -1.f;
		return false;
	}

	const AActor* const Owner = CharacterMovement->GetOwner();
	if (!Owner)
	{
		OutDot = -1.f;
		return false;
	}

	float RightAngle = 0.f;
	bool bMovingRight = false;

	const bool bMovingForward = UMike27BlueprintFunctionLibrary::IsMovingForwardXY(ForwardAngleTollerance, ForwardAngleTollerance, Owner->GetActorForwardVector(), Owner->GetActorRightVector(), CharacterMovement->Velocity, OutDot, RightAngle, bMovingRight);

	OutDot = FMath::Cos(OutDot * UMike27BlueprintFunctionLibrary::GetDegreesToRadiansMultiplier());
	return bMovingForward;
}

// Called every frame
void USprintComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CharacterMovement)
	{
		StopSprint();
		return;
	}

	float ForwardDot = 0.f;
	if (IsMovingForward(ForwardDot))
	{
		CharacterMovement->MaxWalkSpeed = UMike27BlueprintFunctionLibrary::IncrementalValue(OriginalSpeed, SpeedMultiplierIncrement, ForwardDot);
		CharacterMovement->MaxAcceleration = UMike27BlueprintFunctionLibrary::IncrementalValue(OriginalAcceleration, AccelerationMultiplierIncrement, ForwardDot);
		return;
	}
	SetSavedStatsToCharacter();
	// ...
}

