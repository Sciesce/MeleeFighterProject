// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Parent.h"

#include "MeleeFighterCharacter.h"


// Sets default values
AEnemy_Parent::AEnemy_Parent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->SensingInterval = .1f;
	PawnSensingComponent->bSeePawns = true;
	PawnSensingComponent->SightRadius = 1000.f;
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemy_Parent::OnPlayerSeen);
	PawnSensingComponent->SetPeripheralVisionAngle(75.0f);

}

// Called when the game starts or when spawned
void AEnemy_Parent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy_Parent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* AEnemy_Parent::GetBehaviorTree() const
{
	return Tree;
}

void AEnemy_Parent::OnPlayerSeen(APawn* Pawn)
{
	AMeleeFighterCharacter* DetectedPlayer = Cast<AMeleeFighterCharacter>(Pawn);
	if(Pawn)
	{
		isSeeingPlayer = true;
		if(isSeeingPlayer)
		{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Player Detected"));
		}
	}
}
