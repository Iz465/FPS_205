#include "MonsterCharacter.h"
#include "MonsterStats.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AMonsterCharacter::AMonsterCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMonsterCharacter::BeginPlay()
{
    Super::BeginPlay();
    ApplyMonsterStats();
}

void AMonsterCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMonsterCharacter::ApplyMonsterStats()
{
    if (MonsterStats)
    {
        MonsterCurrentHealth = MonsterStats->MonsterHealth;
        GetCharacterMovement()->MaxWalkSpeed = MonsterStats->MonsterMovementSpeed;
        GetCapsuleComponent()->SetCapsuleSize(MonsterStats->MonsterHitbox.X, MonsterStats->MonsterHitbox.Z);
        SetActorScale3D(MonsterStats->MonsterSize);
    }
}

void AMonsterCharacter::MonsterTakeDamage(float MonsterDamageAmount)
{
    float MaxHealth = MonsterStats ? MonsterStats->MonsterHealth : 100.f;
    MonsterCurrentHealth = FMath::Clamp(MonsterCurrentHealth - MonsterDamageAmount, 0.f, MaxHealth);

    if (IsMonsterDead())
    {
        Destroy();
    }
}

void AMonsterCharacter::MonsterAttack(AActor* Target)
{
    if (MonsterStats && Target) {
        UE_LOG(LogTemp, Warning, TEXT("Monster attacks %s for %f damage"), *Target->GetName(), MonsterStats->MonsterDamage);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Monster attack failed: Invalid target or stats."));
    }
}

bool AMonsterCharacter::IsMonsterDead() const
{
    return MonsterCurrentHealth <= 0.f;
}