// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"

#include <string>

#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(StatisticPrompts, All, All)

FString FGeometryData::ToString()
{
	FString Info = "";
	return Info;
}

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
	SetMeshColor(MovementData.MyColor);

	GetWorldTimerManager().SetTimer(TimerName, this, &ABaseGeometryActor::OnTimerFired, MovementData.TimeRate, true);
}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(StatisticPrompts, Error, TEXT("Actor's destroyed"));
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ChangeMyLocation();
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

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, StatString, true, FVector2D(1.5f, 1.5f));	
	}
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

void ABaseGeometryActor::ChangeMyLocation()
{
	switch (MovementData.MoveType)
	{
	case EMovementType::Static:
	{
			break;
	}
	case EMovementType::Sin:
	{
			if (GetWorld())
			{
				float ActualTime = GetWorld()->GetTimeSeconds();
				FVector CurrentLocation = GetActorLocation();
				CurrentLocation.Z = StartLocation.Z + MovementData.Amplitude * FMath::Sin(MovementData.Freq * ActualTime);
				SetActorLocation(CurrentLocation);
			}
			break;
	}
	default: break;
	}
}

void ABaseGeometryActor::SetMeshColor(const FLinearColor& Color)
{
	if (MyStaticMesh)
	{
		UMaterialInstanceDynamic* DynMaterial = MyStaticMesh->CreateAndSetMaterialInstanceDynamic(0);
		if (DynMaterial)
		{
			DynMaterial->SetVectorParameterValue("Color", Color);
		}	
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	if (++MovementData.TimerCount <= MovementData.MaxTimerCount)
	{
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		UE_LOG(StatisticPrompts, Error, TEXT("Timer's count: %i"), MovementData.TimerCount);
		UE_LOG(StatisticPrompts, Error, TEXT("Actor's new color: %s"), *NewColor.ToString());
		SetMeshColor(NewColor);
		OnColorChanged.Broadcast(NewColor, GetName());
	}
	else
	{
		UE_LOG(StatisticPrompts, Error, TEXT("Timer has been stoped"));
		GetWorldTimerManager().ClearTimer(TimerName);
		OnTimerFinished.Broadcast(this);
	}
}