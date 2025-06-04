// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "FPS_205Character.h"
#include "GeometryCacheActor.h" // for spawning geometry cache
#include "GeometryCacheComponent.h"
#include "WeaponsStruct.h"


// Sets default values
ARifle::ARifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ConstructorHelpers::FObjectFinder<UStaticMesh> rifleMesh(TEXT("/Game/Weapons/Rifle/Rifle_2_Mesh.Rifle_2_Mesh"));
	if (rifleMesh.Object) {
		rifle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rifle"));
		rifle->SetStaticMesh(rifleMesh.Object);
		rifle->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		rifle->SetRelativeRotation(FRotator(0, -90, 0));
		
	
	}
	//GunSound = LoadObject<USoundWave>(nullptr, TEXT("/Game/Weapons/Shotgun/shotgun_fire_exported_sound.shotgun_fire_exported_sound"));
	WeaponsStruct rifleWeapon;
	rifleWeapon.name = "Rifle";
	rifleWeapon.fireRate = .2f;
	rifleWeapon.weaponDamage = 15.f;
	rifleWeapon.recoilRate = 0.6f;
	rifleWeapon.recoilLoc = FVector(rifleWeapon.recoilRate * -20, rifleWeapon.recoilRate * -5, 0);
	rifleWeapon.recoilRot = FRotator(rifleWeapon.recoilRate * - 10, 0, 0);
	rifleWeapon.weaponLoc = FVector(-69.113041, 6.829265, -36.745066);
	rifleWeapon.weaponRot = FRotator(11.531901, -253.214561, -27.030231);
	rifleWeapon.meshLoc = FVector(-29.200664, 21.189240, -146.543777);
	rifleWeapon.meshRot = FRotator(-3.513471, -13.486668, -0.387453);
	rifleWeapon.gunSound = LoadObject<USoundWave>(nullptr, TEXT("/Game/Sounds/Gun_Sounds/gun-shot-1-7069.gun-shot-1-7069"));
	rifleWeapon.CamShakeScale = 0.1f;
	rifleWeapon.gunMuzzle = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/MuzzleFlash/MuzzleFlash/Niagara/NS_Rifle_Flash.NS_Rifle_Flash"));
	rifleWeapon.bloodScale = FVector(3, 3, 3);
	rifleWeapon.weaponAbility = "RifleBeam";
	rifleWeapon.abilityCooldown = 20.f;
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

void ARifle::activateMultiShot(USkeletalMeshComponent* playerMesh)
{
	multiShotFired = true;
	AFPS_205Character* player = Cast<AFPS_205Character>(playerMesh->GetOwner());
	player->makeMuzzle(0);
	player->makeMuzzle(-20);
	player->makeMuzzle(20);
	multiShotFired = false;
	

}

void ARifle::WeaponAbility()
{
	multiShot = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.F, FColor::Orange, TEXT("Multi Shot"));

	GetWorldTimerManager().SetTimer(rifleTimer, [this] 
		{
		multiShot = false;
		}, 5.f, false);
	
}


