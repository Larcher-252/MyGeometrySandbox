// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);

UENUM(BlueprintType)
enum class EMovementType :uint8
{
	Static,
	Sin
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float Amplitude = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float Freq = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	EMovementType MoveType = EMovementType::Static;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FLinearColor MyColor = FLinearColor::Yellow;
	
	UPROPERTY(EditAnywhere, Category = "Time")
	float TimeRate = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	int32 MaxTimerCount = 5;
	int32 TimerCount = 0;

	FString ToString();
};

UCLASS()
class MYGEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* MyStaticMesh;

	void SetGeometryData(const FGeometryData& Data) {MovementData = Data;};
	UFUNCTION(BlueprintCallable)
	FGeometryData GetGeometryData() const {return MovementData;};

	UPROPERTY(BlueprintAssignable)
	FOnColorChanged OnColorChanged;
	FOnTimerFinished OnTimerFinished;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	FGeometryData MovementData;
	// Some stats
	UPROPERTY(EditInstanceOnly, Category = "Health")
		float Health = 75.5f;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		int32 Ammo = 200;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		bool IsDead = false;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	FVector StartLocation;
	FTimerHandle TimerName;
	void PrintMyStatsInLog();
	void PrintMyStatsOnScreen();
	void PrintMyTransformInLog();
	void ChangeMyLocation();
	void SetMeshColor(const FLinearColor& Color);
	void OnTimerFired();
};
