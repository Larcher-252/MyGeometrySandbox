// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

UCLASS()
class MYGEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, Category = "Health")
		float Health = 75.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		int32 Ammo = 200;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		bool IsDead = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void PrintMyStatsInLog();
	void PrintMyStatsOnScreen();
};
