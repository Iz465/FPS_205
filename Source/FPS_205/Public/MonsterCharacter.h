#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterStats.h"
#include "MonsterCharacter.generated.h"

UCLASS()
class FPS_205_API AMonsterCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMonsterCharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
    UMonsterStats* MonsterStats;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    float MonsterCurrentHealth;

    void ApplyMonsterStats();
    void MonsterTakeDamage(float MonsterDamageAmount);
    void MonsterAttack(AActor* Target);
    bool IsMonsterDead() const;

    UFUNCTION(BlueprintCallable, Category = "Collision")
    void OnMonsterCollisionWithPlayer(AActor* Player);
};