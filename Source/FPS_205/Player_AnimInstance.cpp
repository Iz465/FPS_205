// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_AnimInstance.h"

UPlayer_AnimInstance::UPlayer_AnimInstance()
{
	;
	UE_LOG(LogTemp, Warning, TEXT("This is most definitely the parent class yes it is."));

}

void UPlayer_AnimInstance::SetupRecoil(FVector RecoilLoc, FRotator RecoilRot)
{
	// how the gun will move when it shoots.
	
	 RecoilLocation = RecoilLoc;


	// how the gun will rotate when it shoots.

	 RecoilRotation = RecoilRot;

	// parameter order is rotation then location then scale.
	 RecoilTransform = FTransform(RecoilRotation, RecoilLocation);
}









