// Fill out your copyright notice in the Description page of Project Settings.

#include "ReorderingObject.h"

// Sets default values
AReorderingObject::AReorderingObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AReorderingObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReorderingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

