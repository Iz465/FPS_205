// Fill out your copyright notice in the Description page of Project Settings.


#include "Shotgun.h"
#include "WeaponsStruct.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AShotgun::AShotgun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh>ShotgunMesh(TEXT("/Game/Weapons/Shotgun/Shotgun_Mesh.Shotgun_Mesh"));
	if (ShotgunMesh.Object) {
		Shotgun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shotgun"));
		Shotgun->SetStaticMesh(ShotgunMesh.Object);
		Shotgun->SetCollisionEnabled(ECollisionEnabled::NoCollision); // No collision so it doesnt collide with the player holding it.
		Shotgun->SetRelativeRotation(FRotator(0, -90, 0));
		
	}
	
	// All weapons are added to the struct to keep the information of them in one place
	// Shotgun has its "isEquipped" bool set to true as its the weapon equipped at the start of the game.
	WeaponsStruct shotgunWeapon;
	shotgunWeapon.name = "Shotgun";
	shotgunWeapon.fireRate = 1.5f;
	shotgunWeapon.recoilRate = 1.5f;
	shotgunWeapon.recoilLoc = FVector(shotgunWeapon.recoilRate * -30, shotgunWeapon.recoilRate * -5, 0);
	shotgunWeapon.recoilRot = FRotator(shotgunWeapon.recoilRate * 25, 0, 0);
	shotgunWeapon.weaponLoc = FVector(-53.749861, 7.656388, -42.136484);
	shotgunWeapon.weaponRot = FRotator(20.104953, -265.705765, -17.647796);
	shotgunWeapon.meshLoc = FVector(-15.656140, 17.940820, -147.398974);
	shotgunWeapon.meshRot = FRotator(-0.000000, -19.783628, 0.000000);
	shotgunWeapon.CamShakeScale = 1.f;
	shotgunWeapon.weaponAbility = "RapidFire";
	shotgunWeapon.isEquipped = true;
	
	bool checkArray = false;


	for (WeaponsStruct& weapon : WeaponsArray)
	{
		if (weapon.name == "Shotgun") {
			checkArray = true;
		}
	}
	if (checkArray == false) {
		WeaponsArray.Add(shotgunWeapon);
	}




	

}

// Called when the game starts or when spawned
void AShotgun::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AShotgun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

