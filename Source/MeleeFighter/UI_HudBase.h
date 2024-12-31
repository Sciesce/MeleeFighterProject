// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDMVVM.h"
#include "UI_HudBase.generated.h"

/**
 * 
 */
UCLASS()
class MELEEFIGHTER_API UUI_HudBase : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetViewModel(UHUDMVVM* InViewModel);

protected:
	//viewmodel reference
	UPROPERTY()
	UHUDMVVM* HUDViewModel;

	virtual void NativeConstruct() override;
	
};
