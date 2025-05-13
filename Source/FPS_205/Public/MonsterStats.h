#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MonsterStats.generated.h"

UCLASS(BlueprintType)
class FPS_205_API UMonsterStats : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    float MonsterHealth = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    float MonsterMovementSpeed = 600.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    float MonsterDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    FVector MonsterHitbox = FVector(40.0f, 40.0f, 40.0f);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    FVector MonsterSize = FVector(1.0f, 1.0f, 1.0f);
};