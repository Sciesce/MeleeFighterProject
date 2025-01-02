// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "Enemy_Parent.generated.h"

UCLASS()
class MELEEFIGHTER_API AEnemy_Parent : public ACharacter
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void OnPlayerSeen(APawn* Pawn);
	// Sets default values for this character's properties
	AEnemy_Parent();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Detection")
	UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Detection")
	bool isSeeingPlayer;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* GetBehaviorTree() const;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess = true))
	UBehaviorTree* Tree;

};
