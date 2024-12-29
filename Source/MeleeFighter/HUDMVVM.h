// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Net/UnrealNetwork.h"
#include "HUDMVVM.generated.h"

/**
 * 
 */
UCLASS()
class MELEEFIGHTER_API UHUDMVVM : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	//variables that will be manipulated
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Stamina", ReplicatedUsing = OnRep_OnStaminaChanged, meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float Stamina;

	// Delegate to notify changes in stamina
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaChanged);
	
	UPROPERTY(BlueprintAssignable, Category = "Stamina")
	FOnStaminaChanged OnStaminaChanged;

	UFUNCTION()
	virtual void OnRep_OnStaminaChanged(){ OnStaminaChanged.Broadcast();}

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override
	{
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);
		DOREPLIFETIME(UHUDMVVM, Stamina);
	}
};
