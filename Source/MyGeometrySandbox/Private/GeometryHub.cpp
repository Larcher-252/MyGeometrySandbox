// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHub.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)

// Sets default values
AGeometryHub::AGeometryHub()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHub::BeginPlay()
{
	Super::BeginPlay();
	//SpawnActor1();
	SpawnActor2();
}

// Called every frame
void AGeometryHub::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeometryHub::SpawnActor1()
{
	UWorld* World = GetWorld();
	if (World)
	{
		for (int32 i = 0; i < 10; i++)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f,300.0f * i,300.0f));
			ABaseGeometryActor* GeomActor = World->SpawnActor<ABaseGeometryActor>(SpawnClass1, GeometryTransform);
			if (GeomActor)
			{
				FGeometryData Data;
				Data.MoveType = FMath::RandBool()? EMovementType::Sin : EMovementType::Static;
				GeomActor->SetGeometryData(Data);
				GeomActor->FinishSpawning(GeometryTransform);
			}
		}
	}
}

void AGeometryHub::SpawnActor2()
{
	UWorld* World = GetWorld();
	if (World)
	{
		for (const FSpawnData GData : SpawnData)
		{
			ABaseGeometryActor* GeomActor = World->SpawnActor<ABaseGeometryActor>(GData.SClass, GData.STransform);
			if (GeomActor)
			{
				GeomActor->SetGeometryData(GData.SData);
				GeomActor->OnColorChanged.AddDynamic(this, &AGeometryHub::OnColorChanged);
				GeomActor->OnTimerFinished.AddUObject(this, &AGeometryHub::OnTimerFinished);
				GeomActor->FinishSpawning(GData.STransform);
			}
		}
	}
}

void AGeometryHub::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogGeometryHub, Warning, TEXT("%s's new color: %s"), *Name, *Color.ToString());
}

void AGeometryHub::OnTimerFinished(AActor* Actor)
{
	if(Actor)
	{
		UE_LOG(LogGeometryHub, Error, TEXT("%s's timer stoped"), *Actor->GetName());

		ABaseGeometryActor* MyActor = Cast<ABaseGeometryActor>(Actor);
		if (!MyActor) return;
		UE_LOG(LogGeometryHub, Error, TEXT("Cast was successful"));
		//Destroy actor
		MyActor->Destroy();
		//Seconds to destroy actor
		//MyActor->SetLifeSpan(2.0f);
	}
}