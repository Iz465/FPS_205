// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"
#include "WeaponsStruct.h"


// Sets default values
ARifle::ARifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	ConstructorHelpers::FObjectFinder<UStaticMesh> rifleMesh(TEXT("/Game/Weapons/Rifle/Rifle_Mesh.Rifle_Mesh"));
	if (rifleMesh.Object) {
		rifle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rifle"));
		rifle->SetStaticMesh(rifleMesh.Object);
		rifle->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		rifle->SetRelativeRotation(FRotator(0, -90, 0));
		
	
	}


	WeaponsStruct rifleWeapon;
	rifleWeapon.name = "Rifle";
	rifleWeapon.fireRate = .6f;
	rifleWeapon.recoilRate = 1.f;
	rifleWeapon.recoilLoc = FVector(rifleWeapon.recoilRate * -40, rifleWeapon.recoilRate * -5, 0);
	rifleWeapon.recoilRot = FRotator(rifleWeapon.recoilRate * - 10, 0, 0);
	rifleWeapon.weaponAbility = "RifleBeam";
	rifleWeapon.isEquipped = false;

	bool checkArray = false;


	// Making sure every weapon has unique name and id
	for (WeaponsStruct& weapon : WeaponsArray)
	{
		if (weapon.name == "Rifle") {
			checkArray = true;
		}
	}
	if (checkArray == false) {
		WeaponsArray.Add(rifleWeapon);
	}

}

// Called when the game starts or when spawned
void ARifle::BeginPlay()
{
	
	Super::BeginPlay();
	
}

// Called every frame
void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

