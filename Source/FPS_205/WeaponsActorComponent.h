// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponsStruct.h"
#include "WeaponsActorComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponsEnum : uint8
{
	Shotgun 	UMETA(DisplayName = "Shotgun"),
	Rifle		UMETA(DisplayName = "Rifle"),
	Pistol		UMETA(DisplayName = "Pistol"),
	AirGun		UMETA(DisplayName = "AirGun")
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_205_API UWeaponsActorComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UWeaponsActorComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EWeaponsEnum CurrentWeapon;
	TMap<FString, EWeaponsEnum> WeaponMap;
		


		
};
