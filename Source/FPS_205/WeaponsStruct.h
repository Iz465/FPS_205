// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
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
	FVector weaponLoc;
	FRotator weaponRot;
	FVector meshLoc;
	FRotator meshRot;
	FVector bloodScale;
	USoundWave* gunSound;
	UNiagaraSystem* gunMuzzle;
	float CamShakeScale;
	bool isEquipped;

};

extern TArray<WeaponsStruct> WeaponsArray;