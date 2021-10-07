// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Display, TEXT("Hello world!"));
	UE_LOG(LogTemp, Warning, TEXT("Hello warning world!"));
	UE_LOG(LogTemp, Error, TEXT("Hello error world!"));

	PrintMyStats();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGeometryActor::PrintMyStats()
{
	float Health = 33.57f;
	int WeaponsCount = 4;
	int Ammo = 100;
	bool IsDead = false;

	UE_LOG(LogTemp, Display, TEXT("Health: %.2f"), Health);
	UE_LOG(LogTemp, Display, TEXT("Count of weapons: %d"), WeaponsCount);
	UE_LOG(LogTemp, Display, TEXT("Ammo: %d"), Ammo);
	UE_LOG(LogTemp, Display, TEXT("Is dead: %d"), IsDead);
}

