// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SprintComponent.generated.h"

class UCharacterMovementComponent;
UCLASS(ClassGroup = (Mike), meta = (BlueprintSpawnableComponent), BlueprintType, Blueprintable)
/* Component that simulates aprinting behaviour on a given Character when moving forward
*/
class MIKE27_API USprintComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USprintComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
	/* Multiplier added to max walk speed when sprinting
	*/
	float SpeedMultiplierIncrement;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
	/* Multiplier added to max acceleration when sprinting
	*/
	float AccelerationMultiplierIncrement;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (UIMin = 0.f, UIMax = 180.f, ClampMin = 0.f, ClampMax = 180.f))
	/* Angle (Degrees) used to determine when facing forward. An angle of 0 means the character will be considered as moving forward when the character forward dir and the movement dir are equal
	*/
	float ForwardAngleTollerance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
	/* If true the component will try to initialize automatically at begin play
	*/
	bool bInitializeAtBeginPlay;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	/* Sets the saved max walking speed and max acceleration to the character movement component
	*/
	void SetSavedStatsToCharacter() const;
private:
	UCharacterMovementComponent* CharacterMovement;
	bool bEnabled;
	float OriginalAcceleration;
	float OriginalSpeed;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Config|Input")
	/* Starts the spint if IsEnabled is true
	*/
	void StartSprint();
	UFUNCTION(BlueprintCallable, Category = "Config|Input")
	/* Stops the sprint
	*/
	void StopSprint();
	UFUNCTION(BlueprintCallable, Category = "Config")
	/* Initializes the component
	*/
	void Initialize(UCharacterMovementComponent* const InCharacter, const bool bInEnabled);
	UFUNCTION(BlueprintCallable, Category = "Config")
	/* Saves the given movement stats
	*/
	void SetSavedMovementStats(const float MaxWalkSpeed, const float MaxAcceleration);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	/* Returns the saved movement stats
	*/
	void GetSavedMovementStats(float& MaxWalkSpeed, float& MaxAcceleration) const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	/* Returns true if sprint is ongoing (true even if speed and acceleration multipliers are not currently applied due to not moving forward)
	*/
	bool IsSprintActive() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	/* Returns true if sprint component is enabled
	*/
	bool IsEnabled() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	/* Returns the max amount of acceleration possible when sprinting
	*/
	float GetMaxAcceleration() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	/* Returns the max amount of walk speed possible when sprinting
	*/
	float GetMaxWalkSpeed() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	/* Returns the Character
	*/
	UCharacterMovementComponent* GetCharacterMovement() const;
	UFUNCTION(BlueprintCallable, Category = "Config")
	/* Sets whetever sprint component is enabled
	*/
	void SetEnabled(const bool bInEnabled);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	/* Returns true in case the character is currently moving forward and the angle (normalized to a range of -1 ... +1 where 1 corresponds to 0 degrees and -1 corresponds to 180 degrees) between the character forward direction and the movement direction
	*@param OutDot the angle (normalized to a range of -1 ... +1 where 1 corresponds to 0 degrees and -1 corresponds to 180 degrees) between the character forward direction and the movement direction
	*@return True if character ismoving forward, flase otherwise
	*/
	bool IsMovingForward(float& OutDot) const;
};
