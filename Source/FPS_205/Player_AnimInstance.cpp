// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"


UPlayer_AnimInstance::UPlayer_AnimInstance()
{
	


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
// #include "AnimNode_ModifyBone.h"

void UPlayer_AnimInstance::GunMovementSway(USkeletalMeshComponent* playerMesh)
{

//	YourMeshComp->SetBoneLocationByName(TEXT("hand_l"), FVector(0, 0, 10), EBoneSpaces::ComponentSpace);
//	YourMeshComp->RefreshBoneTransforms();

}
//YourMeshComp->K2_SetBoneLocationByName(TEXT("hand_l"), FVector(0,0,10), EBoneSpaces::ComponentSpace);
//YourMeshComp->RefreshBoneTransforms();










