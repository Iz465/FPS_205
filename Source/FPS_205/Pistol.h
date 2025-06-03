// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponsStruct.h"
#include "Pistol.generated.h"

class UStaticMeshComponent;
class USkeletalMeshComponent;

UCLASS()
class FPS_205_API APistol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APistol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Pistol;
	virtual void WeaponAbility(USkeletalMeshComponent* playerMesh, WeaponsStruct& pistolWeapon);

};
