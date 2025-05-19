// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponsActorComponent.h"

EWeaponsEnum CurrentWeapon;

// Sets default values for this component's properties
UWeaponsActorComponent::UWeaponsActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CurrentWeapon = EWeaponsEnum::Shotgun;

	// Fill map with string-enum pairs
	//WeaponMap.Add("Shotgun", EWeaponsEnum::Shotgun);
//	WeaponMap.Add("Rifle", EWeaponsEnum::Rifle);
	//WeaponMap.Add("Pistol", EWeaponsEnum::Pistol);
	//WeaponMap.Add("AirGun", EWeaponsEnum::AirGun);

	WeaponMap.Add("Shotgun", EWeaponsEnum::Shotgun);
	WeaponMap.Add("Rifle", EWeaponsEnum::Rifle);
	WeaponMap.Add("Pistol", EWeaponsEnum::Pistol);
	WeaponMap.Add("AirGun", EWeaponsEnum::AirGun);


	// ...
}


// Called when the game starts
void UWeaponsActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponsActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



