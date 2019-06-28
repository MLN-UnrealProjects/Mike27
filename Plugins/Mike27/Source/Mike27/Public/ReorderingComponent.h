// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ReorderingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReordered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreReordered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReorderFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReorderInterrupted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReordering, FTransform, ReorderDestination);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReorderDestinationChanged, FTransform, OldReorderDestination, FTransform, NewReorderDestination);

/**
 *  Component that periodically teleports a scene component to a given location
 */
UCLASS(ClassGroup = (Mike), meta = (BlueprintSpawnableComponent), BlueprintType, Blueprintable)
class MIKE27_API UReorderingComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	FTransform ReorderDestination;
	FTimerHandle DelayHandle;
	FTimerHandle CooldownHandle;
	USceneComponent* Root;

protected:
	virtual void BeginPlay() override;
public:
	UReorderingComponent();

	static float DefaultReorderDelay;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
	/* If true at begin play the component will be initialized automatically
	*/
	bool bInitializeAtBeginplay;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
	/* If true at begin play the current position will be saved (if a Root is setted)
	*/
	bool bSavePositionAtBeginplay;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
	/*
	*/
	float ReorderDelay;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
	/*
	*/
	float ReorderCooldown;

	UPROPERTY(BlueprintAssignable, Category = "Config|Dispatchers")
	/* Event invoked when Reordering destination is changed
	*/
	FOnReorderDestinationChanged OnReorderDestinationChanged;
	UPROPERTY(BlueprintAssignable, Category = "Config|Dispatchers")
	/* Event invoked when Reordering process is over and object has been moved
	*/
	FOnReordered OnReordered;
	UPROPERTY(BlueprintAssignable, Category = "Config|Dispatchers")
	/* Event invoked when Reordering process is over and object has not been moved yet
	*/
	FOnPreReordered OnPreReordered;
	UPROPERTY(BlueprintAssignable, Category = "Config|Dispatchers")
	/* Event invoked when Reordering process fails to execute (mostly because object is not moveable)
	*/
	FOnReorderFailed OnReorderFailed;
	UPROPERTY(BlueprintAssignable, Category = "Config|Dispatchers")
	/* Event invoked when Reordering process is interrupted
	*/
	FOnReorderInterrupted OnReorderInterrupted;
	UPROPERTY(BlueprintAssignable, Category = "Config|Dispatchers")
	/* Event invoked when Reordering process starts
	*/
	FOnReordering OnReordering;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	/*
	*/
	bool IsReordering(float& OutTimeElapsed, float& OutTimeLeft) const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	/*
	*/
	bool IsOnCooldown(float& OutTimeElapsed, float& OutTimeLeft) const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	/*
	*/
	USceneComponent* GetTarget() const;
	UFUNCTION(BlueprintCallable, Category = "Config")
	/*
	*/
	void SetTarget(USceneComponent* const NewTarget, const bool bSaveLocation);
	UFUNCTION(BlueprintCallable, Category = "Config")
	/*
	*/
	void SaveCurrentLocation();
	UFUNCTION(BlueprintCallable, Category = "Config")
	/*
	*/
	void SaveLocation(const FTransform& ToSave);
	UFUNCTION(BlueprintCallable, Category = "Config")
	/*
	*/
	void RestartCooldown();
	UFUNCTION(BlueprintCallable, Category = "Config")
	/*
	*/
	void OnReorder();
private:
	UFUNCTION()
	void OnCooldownOver();
};
