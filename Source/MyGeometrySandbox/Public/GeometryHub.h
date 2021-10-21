// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "GeometryHub.generated.h"

USTRUCT(BlueprintType)
struct FSpawnData
{
	GENERATED_USTRUCT_BODY()

	//Spawn class
	UPROPERTY(EditAnywhere)
	TSubclassOf <ABaseGeometryActor> SClass;

	//Struct of some params
	UPROPERTY(EditAnywhere)
	FGeometryData SData;

	//Location, Rotation and scale
	UPROPERTY(EditAnywhere)
	FTransform STransform;
};

UCLASS()
class MYGEOMETRYSANDBOX_API AGeometryHub : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHub();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Class and its child classes
	UPROPERTY(EditAnywhere)
	TSubclassOf <ABaseGeometryActor> SpawnClass1;
	
	// Instances of class on map
	// ABaseGeometryActor* SpawnClass2;
	
	// Any class
	// UClass* SpawnClass3;

	// dynamic array of struct FSpawnData
	UPROPERTY(EditAnywhere)
	TArray<FSpawnData> SpawnData;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	// 2 spawn actor functions
	void SpawnActor1();
	void SpawnActor2();
	
	UFUNCTION()
	void OnColorChanged(const FLinearColor& Color, const FString& Name);
	void OnTimerFinished(AActor* Actor);
};
