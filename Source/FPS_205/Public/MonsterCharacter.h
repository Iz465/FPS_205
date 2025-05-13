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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Monster")
    UMonsterStats* MonsterStats;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Monster Runtime")
    float MonsterCurrentHealth;

    // Functions
    UFUNCTION(BlueprintCallable, Category = "Monster Actions")
    void MonsterTakeDamage(float MonsterDamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Monster Actions")
    void MonsterAttack(AActor* Target);

    UFUNCTION(BlueprintPure, Category = "Monster")
    bool IsMonsterDead() const;

private:
    void ApplyMonsterStats();
};