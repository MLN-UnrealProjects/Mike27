// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/DamageType.h"

float UHealthComponent::MinMaxHealthValue = 0.01f;

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bStartAtMaxHealth = true;
	MaxHealth = 100.f;
	CurrentHealth = UHealthComponent::MinMaxHealthValue;
	// ...
}
float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}
float UHealthComponent::GetCurrentHealthNormalized() const
{
	return CurrentHealth / MaxHealth;
}
bool UHealthComponent::IsAlive() const
{
	return CurrentHealth > 0.f;
}
void UHealthComponent::SetCurrentHealth(const float NewHealth)
{
	const float PreviousHealth = CurrentHealth;
	CurrentHealth = FMath::Min(NewHealth, MaxHealth);
	if (PreviousHealth > 0.f && CurrentHealth <= 0.f)
	{
		OnDeath.Broadcast();
		return;
	}
	if (PreviousHealth <= 0.f && CurrentHealth > 0.f)
	{
		OnRevive.Broadcast();
	}
}
void UHealthComponent::SetMaxHealthMantainingHealthPercentage(const float NewMaxHealth)
{
	const float HealthNormalized = GetCurrentHealthNormalized();
	MaxHealth = FMath::Max(UHealthComponent::MinMaxHealthValue, NewMaxHealth);
	SetCurrentHealth(HealthNormalized * MaxHealth);
}
void UHealthComponent::SetMaxHealth(const float NewMaxHealth)
{
	MaxHealth = FMath::Max(UHealthComponent::MinMaxHealthValue, NewMaxHealth);
	SetCurrentHealth(CurrentHealth);
}
float UHealthComponent::GetCurrentMaxHealth() const
{
	return MaxHealth;
}
void UHealthComponent::OnAnyDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	SetCurrentHealth(CurrentHealth - Damage);
	OnDamage.Broadcast(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
}
// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bStartAtMaxHealth)
	{
		SetCurrentHealth(MaxHealth);
	}

	AActor* const Owner = GetOwner();
	if (Owner)
	{
		FScriptDelegate Delegate;
		Delegate.BindUFunction(this, TEXT("OnAnyDamageTaken"));
		Owner->OnTakeAnyDamage.Add(Delegate);
	}
	// ...

}
void UHealthComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	AActor* const Owner = GetOwner();
	if (Owner)
	{
		FScriptDelegate Delegate;
		Delegate.BindUFunction(this, TEXT("OnAnyDamageTaken"));
		Owner->OnTakeAnyDamage.Remove(Delegate);
	}
}
