// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_AnimInstance.h"

UPlayer_AnimInstance::UPlayer_AnimInstance()
{
	;
	UE_LOG(LogTemp, Warning, TEXT("This is most definitely the parent class yes it is."));

}

void UPlayer_AnimInstance::SetupRecoil(float recoilAmount)
{
	// how the gun will move when it shoots.
	
	 RecoilLocation = FVector(recoilAmount * -30, recoilAmount * -5, 0);

	// how the gun will rotate when it shoots.
	 RecoilRotation = FRotator(recoilAmount * 25, 0, 0);

	// parameter order is rotation then location then scale.
	 RecoilTransform = FTransform(RecoilRotation, RecoilLocation);
}









