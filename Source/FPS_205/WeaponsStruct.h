// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
// USTRUCT(BlueprintType)
struct FPS_205_API WeaponsStruct
{  // add uproperty to them.
	FString name;
	float fireRate;
	float recoilRate;
	FVector recoilLoc;
	FRotator recoilRot;
	FString weaponAbility;
	bool isEquipped;

};

extern TArray<WeaponsStruct> WeaponsArray;