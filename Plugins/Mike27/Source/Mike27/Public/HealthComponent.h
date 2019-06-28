// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AController;
class UDamageType;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRevive);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnDamage, AActor*, DamagedActor, float, Damage, const UDamageType*, DamageType, AController*, DamageInstigator, AActor*, DamageDealer);

UCLASS(ClassGroup = (Mike), meta = (BlueprintSpawnableComponent), BlueprintType, Blueprintable)
/* Component responsible to keep track of damage received and current health
*/
class MIKE27_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	static float MinMaxHealthValue;

	UPROPERTY(BlueprintAssignable, Category = "Config|Dispatchers")
	/* Event launched on death
	*/
	FOnDeath OnDeath;
	UPROPERTY(BlueprintAssignable, Category = "Config|Dispatchers")
	/* Event launched revive
	*/
	FOnRevive OnRevive;
	UPROPERTY(BlueprintAssignable, Category = "Config|Dispatchers")
	/* Event lauched when damage is received
	*/
	FOnDamage OnDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
	bool bStartAtMaxHealth;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	/* Returns the current health value
	*/
	float GetCurrentHealth() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	/* Returns the current health value normalized between 0 and 1
	*/
	float GetCurrentHealthNormalized() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	/* True if Current Health is more than 0
	*/
	bool IsAlive() const;
	UFUNCTION(BlueprintCallable, Category = "Config")
	/* Sets current health
	*/
	void SetCurrentHealth(const float NewHealth);
	UFUNCTION(BlueprintCallable, Category = "Config")
	/* Sets MaxHealth while mantaining the current health normalized value
	*/
	void SetMaxHealthMantainingHealthPercentage(const float NewMaxHealth);
	UFUNCTION(BlueprintCallable, Category = "Config")
	/* Sets MaxHealth
	*/
	void SetMaxHealth(const float NewMaxHealth);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	/* Returns the current max health value
	*/
	float GetCurrentMaxHealth() const;

	void OnComponentDestroyed(bool bDestroyingHierarchy) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Config", meta = (UIMin = 0.f, ClampMin = 0.f, AllowPrivateAccess = "true"))
	float MaxHealth;

	float CurrentHealth;

	UFUNCTION()
	void OnAnyDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
