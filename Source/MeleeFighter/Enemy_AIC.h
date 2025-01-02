// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy_AIC.generated.h"

/**
 * 
 */
UCLASS()
class MELEEFIGHTER_API AEnemy_AIC : public AAIController
{
	GENERATED_BODY()

public:
	explicit AEnemy_AIC(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
