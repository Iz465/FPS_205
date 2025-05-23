// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol.h"
#include "WeaponsStruct.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APistol::APistol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ConstructorHelpers::FObjectFinder<UStaticMesh>PistolMesh(TEXT("/Game/Weapons/Pistol/base.base"));
	if (!PistolMesh.Object) return; 
	
		Pistol = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pistol"));
		Pistol->SetStaticMesh(PistolMesh.Object);
		Pistol->SetCollisionEnabled(ECollisionEnabled::NoCollision); // No collision so it doesnt collide with the player holding it.
		Pistol->SetRelativeRotation(FRotator(0, -90, 0));
		Pistol->SetWorldScale3D(FVector(.5, .5, .5));
		
		WeaponsStruct PistolWeapon;
		PistolWeapon.name = "Pistol";
		PistolWeapon.fireRate = 0.5f; 
		PistolWeapon.recoilRate = 1.f; 
		PistolWeapon.recoilLoc = FVector(PistolWeapon.recoilRate * -30, PistolWeapon.recoilRate * -5, 0);
		PistolWeapon.recoilRot = FRotator(PistolWeapon.recoilRate * 25, 0, 0);
		PistolWeapon.weaponLoc = FVector(-66.233594, 2.383527, -29.492753);
		PistolWeapon.weaponRot = FRotator(17.830860, 96.242544, -19.460437);
		PistolWeapon.meshLoc = FVector(-23.135406, 37.212458, -143.116496);
		PistolWeapon.meshRot = FRotator(1.002553, 0.563082, -0.510769);
		PistolWeapon.gunSound = LoadObject<USoundWave>(nullptr, TEXT("/Game/Sounds/Gun_Sounds/pistol_gun_sound.pistol_gun_sound"));
		PistolWeapon.CamShakeScale = 0.2f; 
		PistolWeapon.gunMuzzle = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/MuzzleFlash/MuzzleFlash/Niagara/NS_Rifle_Flash.NS_Rifle_Flash"));
		PistolWeapon.bloodScale = FVector(3, 3, 3);
		PistolWeapon.weaponAbility = "TestAbility";
		PistolWeapon.isEquipped = false;

		bool checkArray = false;


		for (WeaponsStruct& weapon : WeaponsArray)
		{
			if (weapon.name == "Pistol") {
				checkArray = true;
			}
		}
		if (checkArray == false) {
			WeaponsArray.Add(PistolWeapon);
		}

}

// Called when the game starts or when spawned
void APistol::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APistol::WeaponAbility()
{
}



/*
* 
* old rotation/ location in case i want to switch back to this one.
	PistolWeapon.weaponLoc = FVector(-65.756018, 1.757550, -31.527866);
		PistolWeapon.weaponRot = FRotator(23.375090, 107.144062, -12.869051);
		PistolWeapon.meshLoc = FVector(-33.758897, 35.569133, -142.992237);
		PistolWeapon.meshRot = FRotator(0.897862, -6.448737, 0.776268);

*/