// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Parent.h"

#include "Editor/PropertyEditor/Private/EditConditionParserTests.h"

// Sets default values
AWeapon_Parent::AWeapon_Parent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//initialize components
	//initialize weapon root SM (may change)
	WeaponRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponRoot"));
	RootComponent = WeaponRoot; //setting as root component

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(WeaponRoot);

	WeaponHandle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponHandle"));
	WeaponHandle->SetupAttachment(WeaponRoot);

	WeaponCore = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponCore"));
	WeaponCore->SetupAttachment(WeaponRoot);
	
	WeaponCore->SetMaterial(1, NeutralWeaponColor);

}

// Called when the game starts or when spawned
void AWeapon_Parent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon_Parent::SetWeaponColor(int32 Index)
{
	UMaterialInstance* NewMaterialInstance = nullptr;
	
	switch (Index)
	{
	case 1:
		NewMaterialInstance = NeutralWeaponColor;
		break;

	case 2:
		NewMaterialInstance = PrimaryAttackColor;
		break;
		
	case 3:
		NewMaterialInstance = SecondaryAttackColor;
		break;

	default:
		
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Invalid index"));
		return;
	}

	if (!NewMaterialInstance)
	{
		return;
	}

	WeaponCore-> SetMaterial(0, NewMaterialInstance);

	
}


