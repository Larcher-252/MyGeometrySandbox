// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(StatisticPrompts, All, All)

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
	PrintMyStatsInLog();
	PrintMyStatsOnScreen();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseGeometryActor::PrintMyStatsInLog()
{
	float Health = 33.57f;
	int Ammo = 100;
	bool IsDead = false;

	UE_LOG(StatisticPrompts, Display, TEXT("Health: %.2f"), Health);
	UE_LOG(StatisticPrompts, Display, TEXT("Ammo: %d"), Ammo);
	UE_LOG(StatisticPrompts, Display, TEXT("Is dead: %d"), IsDead);
}

void ABaseGeometryActor::PrintMyStatsOnScreen()
{
	float Healt = 75.5f;
	FString StringHealth = "HP = " + FString::SanitizeFloat(Healt);
	int Ammo = 200;
	FString StringAmmo = "AMMO = " + FString::FromInt(Ammo);
	bool IsDead = false;
	FString StringIsDead = "Is dead = " + FString(IsDead ? "true" : "false");

	FString StatString = FString::Printf(TEXT("--All stat--\n %s \n %s \n %s"), *StringHealth, *StringAmmo, *StringIsDead);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, StatString, true, FVector2D(1.5f, 1.5f));
}

