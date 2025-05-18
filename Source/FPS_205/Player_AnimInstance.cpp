// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_AnimInstance.h"
// #include "Math/UnrealMathUtility.h"
#include "Components/SkeletalMeshComponent.h"


UPlayer_AnimInstance::UPlayer_AnimInstance()
{
	


}

// Sets the recoil values to  be used in the ImplementRecoil function
void UPlayer_AnimInstance::SetupRecoil(FVector RecoilLoc, FRotator RecoilRot)
{
	// how the gun will move when it shoots.
	
	 RecoilLocation = RecoilLoc;

	// how the gun will rotate when it shoots.

	 RecoilRotation = RecoilRot;

	// parameter order is rotation then location then scale.
	 RecoilTransform = FTransform(RecoilRotation, RecoilLocation);
}

// Users Interp to make the recoil work. Called in BP
void UPlayer_AnimInstance::ImplementRecoil(float deltaTime)
{
	FTransform Empty;

	Recoil.SetLocation(FMath::VInterpTo(Recoil.GetLocation(), RecoilTransform.GetLocation(), deltaTime, 10.0f));
	Recoil.SetRotation(FQuat::Slerp(Recoil.GetRotation(), RecoilTransform.GetRotation(), deltaTime * 10.0f));
//	Recoil = FMath::FInterpTo(Recoil, RecoilTransform, deltaTime, 10);

//	RecoilTransform = FMath::FInterpTo(RecoilTransform, Empty, deltaTime, 10);
	RecoilTransform.SetLocation(FMath::VInterpTo(RecoilTransform.GetLocation(), Empty.GetLocation(), deltaTime, 10.0f));
	RecoilTransform.SetRotation(FQuat::Slerp(RecoilTransform.GetRotation(), Empty.GetRotation(), deltaTime * 10.0f));

}

// Called in BP
void UPlayer_AnimInstance::SetupGunSway()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, TEXT("Gun Sway Updating"));
	// need to make this the same regardless of frames.
	gunSwaySpeed += 0.01;

	float locZ = FMath::Lerp(gunSwayLocZ, finalGunSwayLocZ, gunSwaySpeed);
	float rotX = FMath::Lerp(gunSwayRotX, finalGunSwayRotX, gunSwaySpeed);
	float rotZ = FMath::Lerp(gunSwayRotZ, finalGunSwayRotZ, gunSwaySpeed);
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::SanitizeFloat(locZ));

	// Starts the gun sway
	if (!resetTransform) {
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, TEXT("Reset False"));
		GunSwayTransform.SetLocation(FVector(0,0, locZ));
		GunSwayTransform.SetRotation(FRotator(rotX, 0, rotZ).Quaternion());

		if (gunSwaySpeed >= 1) {

			gunSwayLocZ = finalGunSwayLocZ;
			finalGunSwayLocZ = 0;
			gunSwayRotX = finalGunSwayRotX;
			finalGunSwayRotX = 0;
			gunSwayRotZ = finalGunSwayRotZ;
			finalGunSwayRotZ = 0;

			gunSwaySpeed = 0;
			resetTransform = true;

		}


	}


	// This will reset the gun sway, making the gun go back to its original location
	else {
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, TEXT("Reset True"));
		GunSwayTransform.SetLocation(FVector(0, 0, locZ));
		GunSwayTransform.SetRotation(FRotator(rotX, 0, rotZ).Quaternion());

		if (gunSwaySpeed >= 1) {
			
			finalGunSwayLocZ = gunSwayLocZ;
			gunSwayLocZ = 0;
			finalGunSwayRotX = gunSwayRotX;
			gunSwayRotX = 0;
			finalGunSwayRotZ = gunSwayRotZ;
			gunSwayRotZ = 0;
		
			gunSwaySpeed = 0;
			resetTransform = false;
		}

	}
}



void UPlayer_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	

}













