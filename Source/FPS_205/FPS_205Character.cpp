// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_205Character.h"
#include "GunCameraShake.h"
#include "FPS_205Projectile.h"
#include "WeaponsStruct.h"
#include "WeaponsActorComponent.h"
#include "Animation/AnimInstance.h"
#include "Player_AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ChildActorComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "DrawDebugHelpers.h" // Allows line trace to be seen.
#include "NiagaraSystem.h" // for spawning niagara VFX
#include "NiagaraFunctionLibrary.h"
#include "GeometryCacheActor.h" // for spawning geometry cache
#include "GeometryCacheComponent.h"
#include "GeometryCache.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AFPS_205Character

AFPS_205Character::AFPS_205Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	ConstructorHelpers::FObjectFinder<USkeletalMesh>Mesh1PSkeleton(TEXT("/Game/FirstPersonArms/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms"));
	if (Mesh1PSkeleton.Object) {
		Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
		Mesh1P->SetSkeletalMesh(Mesh1PSkeleton.Object);
		Mesh1P->SetOnlyOwnerSee(true);
		Mesh1P->SetupAttachment(FirstPersonCameraComponent);
		Mesh1P->bCastDynamicShadow = false;
		Mesh1P->CastShadow = false;
		Mesh1P->SetRelativeLocation(FVector(-15.656140, 17.940820, -147.398974));
		Mesh1P->SetRelativeRotation(FRotator(-0.000000, -19.783628, 0.000000));
		
	}


	ConstructorHelpers::FClassFinder<UAnimInstance>PlayerAnimBP(TEXT("/Game/FirstPerson/Animations/Player_Anim_BP.Player_Anim_BP_C"));

	// If the Animation class is found then the player will use that as its animation blueprint
	if (PlayerAnimBP.Class) { 
		GetMesh1P()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh1P()->SetAnimInstanceClass(PlayerAnimBP.Class);
	}



	ConstructorHelpers::FClassFinder<AActor> WeaponClass(TEXT("/Game/Weapons/Shotgun/Shotgun_BP.Shotgun_BP_C")); // Finds the shotgun that will be equipped at the start.
	if (WeaponClass.Class) {
		
		Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon")); // The gun the player holds.
		Weapon->SetupAttachment(Mesh1P);
		Weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("weapon_r_muzzle"));
		Weapon->SetChildActorClass(WeaponClass.Class);
		Weapon->SetRelativeLocation(FVector(-53.749861, 7.656388, -42.136484));
		Weapon->SetRelativeRotation(FRotator(20.104953, -265.705765, -17.647796));
		Weapon->SetWorldScale3D(FVector(0.500000, 0.500000, 0.500000));

	
	}

	BoxAim = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxAim")); // This is where the gun will shoot from, where the sound will come from.
	BoxAim->SetupAttachment(Weapon);
	BoxAim->SetRelativeLocation(FVector(-0.050040, 92.949743, 61.420402));
	BoxAim->SetRelativeRotation(FRotator(2.913176, 92.569598, 355.608232));
	BoxAim->SetWorldScale3D(FVector(0.100000, 0.100000, 0.100000));

	WeaponsActorComponent = CreateDefaultSubobject<UWeaponsActorComponent>(TEXT("WeaponsActorComponent"));

}

//////////////////////////////////////////////////////////////////////////// Input

void AFPS_205Character::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AFPS_205Character::BeginPlay()
{
	Super::BeginPlay();
	for (WeaponsStruct& weapon : WeaponsArray) {
		if (weapon.name == "Shotgun") {
			weapon.isEquipped = true;
		}
		else {
			weapon.isEquipped = false;
		}
	}


}

void AFPS_205Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPS_205Character::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPS_205Character::Look);

		//// Shooting 
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AFPS_205Character::Shooting);

		//Shotgun
		EnhancedInputComponent->BindAction(ShotgunAction, ETriggerEvent::Started, this, &AFPS_205Character::EquipShotgun);

		//Rifle 
		EnhancedInputComponent->BindAction(RifleAction, ETriggerEvent::Started, this, &AFPS_205Character::EquipRifle);

		//Pistol 
		EnhancedInputComponent->BindAction(PistolAction, ETriggerEvent::Started, this, &AFPS_205Character::EquipPistol);

	
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


// All gun things are played here like the sound, the animation, the recoil etc.
void AFPS_205Character::Shooting()
{
	
	if (!canFire) return;

		canFire = false;

		for (const WeaponsStruct& weapon : WeaponsArray) {
			if (weapon.isEquipped == true) {
				specificWeapon = &weapon;
				break;
			}
		}

		if (!specificWeapon) return;

			PlayerAnimInstance = Cast<UPlayer_AnimInstance>(GetMesh1P()->GetAnimInstance());
			if (!PlayerAnimInstance) return;

			PlayerAnimInstance->SetupRecoil(specificWeapon->recoilLoc, specificWeapon->recoilRot);
			

			FVector StartLoc = BoxAim->GetComponentLocation();
			FVector ForwardVector = BoxAim->GetForwardVector();
			FVector EndLoc = ((ForwardVector * 5000.f) + StartLoc);
			FHitResult TraceResult;
		
			bool TraceHit = GetWorld()->LineTraceSingleByChannel(TraceResult, StartLoc, EndLoc, ECC_Visibility);

			if (TraceHit) {
		
				// if an actor is hit, then the blood splatter will appear where the actor was hit.
				AActor* ActorHit = TraceResult.GetActor();
				if (ActorHit)
				{
					UGeometryCache* BloodCache = LoadObject<UGeometryCache>(nullptr, TEXT("/Game/Blood_Splatter_03.Blood_Splatter_03"));
					if (BloodCache)
					{
						FVector bloodLocation = TraceResult.ImpactPoint;
						FRotator bloodRotation = TraceResult.ImpactNormal.Rotation();

						AGeometryCacheActor* BloodSplatter = GetWorld()->SpawnActor<AGeometryCacheActor>(bloodLocation, bloodRotation);
						BloodSplatter->GetGeometryCacheComponent()->SetGeometryCache(BloodCache);
						BloodSplatter->GetGeometryCacheComponent()->Play();
						BloodSplatter->SetActorScale3D(specificWeapon->bloodScale);
						BloodSplatter->SetLifeSpan(.5f);
					}
				}
			}
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), specificWeapon->gunSound, BoxAim->GetComponentLocation());

			if (specificWeapon->gunMuzzle) {
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), specificWeapon->gunMuzzle, BoxAim->GetComponentLocation(), BoxAim->GetForwardVector().Rotation(), FVector(1),
					true, true, ENCPoolMethod::AutoRelease, true);
			}

			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(UGunCameraShake::StaticClass(), specificWeapon->CamShakeScale);

			// Sets up a timer so the gun can only fire every x seconds
			GetWorldTimerManager().SetTimer(GunWait, [this]()
				{
					canFire = true;
				}, specificWeapon->fireRate, false);	
}
 






 void AFPS_205Character::EquipGun(UClass* GunClass, FString weaponName) {
	 
	 if (!GunClass) return;

		 canFire = true;
		 Weapon->SetChildActorClass(GunClass);

		 for (WeaponsStruct& weapon : WeaponsArray) {
			 if (weapon.name == weaponName) {
				 weapon.isEquipped = true;

				 Weapon->SetRelativeLocation(weapon.weaponLoc);
				 Weapon->SetRelativeRotation(weapon.weaponRot);
				 Mesh1P->SetRelativeLocation(weapon.meshLoc); 
				 Mesh1P->SetRelativeRotation(weapon.meshRot);
	
				 if (EWeaponsEnum* EnumWeapon = WeaponsActorComponent->WeaponMap.Find(weaponName)) {
					 WeaponsActorComponent->CurrentWeapon = *EnumWeapon;
				 }
			 }

			 else {
				 weapon.isEquipped = false;
			 }
		 }
	 }
 
 
void AFPS_205Character::EquipShotgun()
{
	UClass* ShotgunClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/Weapons/Shotgun/Shotgun_BP.Shotgun_BP_C"));
	EquipGun(ShotgunClass, "Shotgun");
}


void AFPS_205Character::EquipRifle()
{
	UClass* RifleClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/Weapons/Rifle/Rifle_BP.Rifle_BP_C"));
	EquipGun(RifleClass, "Rifle");
}

void AFPS_205Character::EquipPistol()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("pistol keybind activated"));
	UClass* PistolClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/Weapons/Pistol/Pistol_BP.Pistol_BP_C"));
	EquipGun(PistolClass, "Pistol");
} 


	




void AFPS_205Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{

		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
		
		/*UPlayer_AnimInstance* playerAnim = Cast<UPlayer_AnimInstance>(GetMesh1P()->GetAnimInstance());
		if (playerAnim) {
			playerAnim->GunMovementSway(GetMesh1P());
		} */
		
	}
}

void AFPS_205Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}