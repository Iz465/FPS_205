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
		PistolWeapon.weaponLoc = FVector(-53.749861, 7.656388, -42.136484);
		PistolWeapon.weaponRot = FRotator(20.104953, -265.705765, -17.647796);
		PistolWeapon.meshLoc = FVector(-15.656140, 17.940820, -147.398974);
		PistolWeapon.meshRot = FRotator(-0.000000, -19.783628, 0.000000);
		PistolWeapon.gunSound = LoadObject<USoundWave>(nullptr, TEXT(""));
		PistolWeapon.CamShakeScale = 0.2f;
		PistolWeapon.gunMuzzle = LoadObject<UNiagaraSystem>(nullptr, TEXT(""));
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

