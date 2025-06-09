// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyParent.h"

// Sets default values
AEnemyParent::AEnemyParent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyParent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyParent::DeleteBodyParts(AActor* bodyPart)
{
	FTimerHandle deleteTimer;

    GetWorldTimerManager().SetTimer(deleteTimer, [this, bodyPart]()
        {
			GEngine->AddOnScreenDebugMessage(01, 5.f, FColor::Silver, TEXT("Deleting body parts"));
            bodyPart->Destroy();
        }, 60.f, false);

	
}

void AEnemyParent::CallDelete(AActor* bodyPart)
{
	bodyPart->Destroy();
}

