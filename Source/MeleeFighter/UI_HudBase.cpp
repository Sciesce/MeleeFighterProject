// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_HudBase.h"
#include "HUDMVVM.h"

void UUI_HudBase::SetViewModel(UHUDMVVM* InViewModel)
{
	//Viewmodel = InViewModel;
	if(HUDViewModel != InViewModel)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Viewmodel Could be set"));
		
	}
	
}

void UUI_HudBase::NativeConstruct()
{
	Super::NativeConstruct();
}


