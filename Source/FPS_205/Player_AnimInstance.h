// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Engine/SkeletalMesh.h"
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
	void SetupRecoil(float recoilAmount);

	UPROPERTY(BlueprintReadWrite)
	FTransform Recoil;
	UPROPERTY(BlueprintReadWrite)
	FTransform RecoilTransform;
	FVector RecoilLocation;
	FRotator RecoilRotation;

protected:

private:
	USkeletalMesh* animSkeleton;
	
	

};
