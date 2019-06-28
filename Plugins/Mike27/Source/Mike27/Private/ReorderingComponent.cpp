// Fill out your copyright notice in the Description page of Project Settings.

#include "ReorderingComponent.h"
#include "Mike27BlueprintFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"

float UReorderingComponent::DefaultReorderDelay = 0.01f;
UReorderingComponent::UReorderingComponent()
{
	bInitializeAtBeginplay = true;
	bSavePositionAtBeginplay = true;
	ReorderDelay = 5.f;
	ReorderCooldown = 10.f;

	DelayHandle.Invalidate();
	CooldownHandle.Invalidate();

	ReorderDestination = FTransform::Identity;
	Root = nullptr;
}
bool UReorderingComponent::IsReordering(float& OutTimeElapsed, float& OutTimeLeft) const
{
	return UMike27BlueprintFunctionLibrary::IsTimerValid(this, DelayHandle, OutTimeLeft, OutTimeElapsed);
}
bool UReorderingComponent::IsOnCooldown(float& OutTimeElapsed, float& OutTimeLeft) const
{
	return UMike27BlueprintFunctionLibrary::IsTimerValid(this, CooldownHandle, OutTimeLeft, OutTimeElapsed);
}
void UReorderingComponent::BeginPlay()
{
	Super::BeginPlay();
	const AActor* const Owner = GetOwner();
	if (bInitializeAtBeginplay)
	{
		SetTarget((Owner ? Owner->GetRootComponent() : nullptr), bSavePositionAtBeginplay);
	}
	else if (bSavePositionAtBeginplay)
	{
		SaveCurrentLocation();
	}
}
USceneComponent* UReorderingComponent::GetTarget() const
{
	return Root;
}
void UReorderingComponent::SaveCurrentLocation()
{
	if (Root)
	{
		SaveLocation(Root->GetComponentTransform());
	}
}
void UReorderingComponent::SaveLocation(const FTransform& ToSave)
{
	OnReorderDestinationChanged.Broadcast(ReorderDestination, ToSave);
	ReorderDestination = ToSave;
}
void UReorderingComponent::RestartCooldown()
{
	const UWorld* const World = GetWorld();
	if (World)
	{
		FTimerManager& Manager = World->GetTimerManager();
		Manager.ClearTimer(CooldownHandle);
		Manager.ClearTimer(DelayHandle);

		if (Root)
		{
			if (ReorderCooldown <= 0.f)
			{
				OnCooldownOver();
			}
			else
			{
				Manager.SetTimer(CooldownHandle, this, &UReorderingComponent::OnCooldownOver, ReorderCooldown, false);
			}
		}
	}
}
void UReorderingComponent::SetTarget(USceneComponent* const NewTarget, const bool bSaveLocation)
{
	if (Root != NewTarget)
	{
		Root = NewTarget;
		if (bSaveLocation)
		{
			SaveCurrentLocation();
		}
		RestartCooldown();
	}
	else if (bSaveLocation)
	{
		SaveCurrentLocation();
	}
}
void UReorderingComponent::OnCooldownOver()
{
	OnReordering.Broadcast(ReorderDestination);

	//To avoid infinite loop
	if (ReorderDelay <= 0.f && ReorderCooldown <= 0.f)
	{
		ReorderDelay = UReorderingComponent::DefaultReorderDelay;
	}

	const UWorld* const World = GetWorld();
	if (World)
	{
		FTimerManager& Manager = World->GetTimerManager();
		Manager.ClearTimer(CooldownHandle);
		Manager.ClearTimer(DelayHandle);

		if (Root)
		{
			if (ReorderDelay <= 0.f)
			{
				OnReorder();
			}
			else
			{
				Manager.SetTimer(DelayHandle, this, &UReorderingComponent::OnReorder, ReorderDelay, false);
			}
		}
	}
}
void UReorderingComponent::OnReorder()
{
	float TimeElapsed = 0.f;
	float TimeLeft = 0.f;
	IsReordering(TimeElapsed, TimeLeft);
	if (TimeLeft > 0.f)
	{
		OnReorderInterrupted.Broadcast();
	}
	if (Root)
	{
		if (Root->Mobility == EComponentMobility::Type::Movable)
		{
			OnPreReordered.Broadcast();
			Root->SetWorldTransform(ReorderDestination, false, nullptr, ETeleportType::ResetPhysics);
			OnReordered.Broadcast();
		}
		else
		{
			OnReorderFailed.Broadcast();
		}
	}

	RestartCooldown();
}
