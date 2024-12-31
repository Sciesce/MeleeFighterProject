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

/*private:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
	int CurrentStamina;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
	int MaxStamina;

public:
	void SetCurrentStamina(int32 NewCurrentStamina)
	{
		if (UE_MVVM_SET_PROPERTY_VALUE(CurrentStamina, NewCurrentStamina))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
		}
	}

	void SetMaxStamina(int32 NewMaxStamina)
	{
		if (UE_MVVM_SET_PROPERTY_VALUE(MaxStamina, NewMaxStamina))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
		}
	}

	int32 GetCurrentStamina() const
	{
		return CurrentStamina;
	}

	int32 GetMaxStamina() const
	{
		return MaxStamina;
	}

public:

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetStaminaPercent() const
	{
		if (MaxStamina != 0)
		{
			return (float) CurrentStamina / (float) MaxStamina;
		}
		else
		{
			return 0;
		}
	}*/



	
/*
public:
	//variables that will be manipulated
	/*UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stamina", ReplicatedUsing = OnRep_OnStaminaChanged, meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float Stamina;#1#

	// Delegate to notify changes in stamina
	/*DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaChanged);
	
	UPROPERTY(BlueprintAssignable, Category = "Stamina")
	FOnStaminaChanged OnStaminaChanged;

	UFUNCTION()
	virtual void OnRep_OnStaminaChanged(){ OnStaminaChanged.Broadcast();}#1#

	/*virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override
	{
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);
		DOREPLIFETIME(UHUDMVVM, Stamina);
	}#1#
	
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetStaminaPercent() const
	{
		if (MaxStamina != 0)
		{
			return Stamina / MaxStamina;
		}
		else
		{
			return 0;
		}
	}

	void SetStamina(float NewStamina)
	{
		if (UE_MVVM_SET_PROPERTY_VALUE(Stamina, NewStamina));
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
		}
	}

protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Getter)
	float Stamina;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Getter)
	float MaxStamina;

private:*/
	
};
