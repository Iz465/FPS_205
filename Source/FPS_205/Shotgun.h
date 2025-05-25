// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponsStruct.h"
#include "Shotgun.generated.h"

class UStaticMeshComponent;
class UPlayer_AnimInstance;
class USkeletalMeshComponent;
class AFPS_205Character;
//TArray WeaponsArray;

UCLASS()
class FPS_205_API AShotgun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShotgun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Shotgun;
	UPlayer_AnimInstance* playerAnimInstance; 
	virtual void WeaponAbility(USkeletalMeshComponent* playerMesh, const WeaponsStruct& shotgunWeapon);
	FTimerHandle rapidfireTimer;
	bool fireAbility = true;
	AFPS_205Character* player;
	int count = 0;
	float delay;

};
