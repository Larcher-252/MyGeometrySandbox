// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(StatisticPrompts, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("SecondMeshName");
	SetRootComponent(MyStaticMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	//PrintMyTransformInLog();
	//PrintMyStatsInLog();
	//PrintMyStatsOnScreen();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float ActualTime = GetWorld()->GetTimeSeconds();
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.Z = StartLocation.Z + Amplitude * FMath::Sin(Freq * ActualTime);
	SetActorLocation(CurrentLocation);
}

void ABaseGeometryActor::PrintMyStatsInLog()
{
	UE_LOG(StatisticPrompts, Warning, TEXT("Actor's name: %s"), *GetName());
	UE_LOG(StatisticPrompts, Warning, TEXT("Health: %.2f"), Health);
	UE_LOG(StatisticPrompts, Warning, TEXT("Ammo: %d"), Ammo);
	UE_LOG(StatisticPrompts, Warning, TEXT("Is dead: %d"), IsDead);
}

void ABaseGeometryActor::PrintMyStatsOnScreen()
{
	FString StringHealth = "HP = " + FString::SanitizeFloat(Health);
	FString StringAmmo = "AMMO = " + FString::FromInt(Ammo);
	FString StringIsDead = "Is dead = " + FString(IsDead ? "true" : "false");

	FString StatString = FString::Printf(TEXT("--All stat--\n %s \n %s \n %s"), *StringHealth, *StringAmmo, *StringIsDead);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, StatString, true, FVector2D(1.5f, 1.5f));
}

void ABaseGeometryActor::PrintMyTransformInLog()
{
	FTransform MyMeshTransform = GetActorTransform();
	FVector MyMeshLocation = MyMeshTransform.GetLocation();
	FRotator MyMeshRotator = MyMeshTransform.Rotator();
	FVector MyMeshScale = MyMeshTransform.GetScale3D();

	UE_LOG(StatisticPrompts, Error, TEXT("Actor's name: %s"), *GetName());
	UE_LOG(StatisticPrompts, Error, TEXT("Actor's transform: %s"), *MyMeshTransform.ToHumanReadableString());
	UE_LOG(StatisticPrompts, Error, TEXT("Actor's location: %s"), *MyMeshLocation.ToString());
	UE_LOG(StatisticPrompts, Error, TEXT("Actor's rotation: %s"), *MyMeshRotator.ToString());
	UE_LOG(StatisticPrompts, Error, TEXT("Actor's scale: %s"), *MyMeshScale.ToString());
}

