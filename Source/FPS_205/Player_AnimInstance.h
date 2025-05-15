// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Engine/SkeletalMesh.h"
#include "Logging/LogMacros.h"
#include "Player_AnimInstance.generated.h"

class USkeletalMesh;
/**
 * 
 */
UCLASS()
class FPS_205_API UPlayer_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayer_AnimInstance();

	UFUNCTION(BlueprintCallable)
	void SetupRecoil(FVector RecoilLoc, FRotator RecoilRot);
	UFUNCTION(BlueprintCallable)
	void ImplementRecoil(float deltaTime);
	UFUNCTION(BlueprintCallable)
	void SetupGunSway();
	


	// Variables for recoil
	UPROPERTY(BlueprintReadWrite)
	FTransform Recoil;
	UPROPERTY(BlueprintReadWrite)
	FTransform RecoilTransform;
	FVector RecoilLocation;
	FRotator RecoilRotation;
	FVector WeaponLocation;

	// Variables for gun sway
	UPROPERTY(BlueprintReadWrite)
	FTransform GunSwayTransform;
	UPROPERTY(BlueprintReadWrite)
	FTransform FinalGunSwayTransform;
	float gunSwaySpeed = 0;
	float gunSwayLocZ = 0;
	float gunSwayRotX = 0;
	float gunSwayRotZ = 0;
	float finalGunSwayLocZ = 1;
	float finalGunSwayRotX = 1.7;
	float finalGunSwayRotZ = 0.5;
	bool resetTransform = false;



protected:

private:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	USkeletalMesh* animSkeleton;
	
	

};
