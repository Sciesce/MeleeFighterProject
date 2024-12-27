// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Weapon_Parent.generated.h"

UCLASS()
class MELEEFIGHTER_API AWeapon_Parent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Parent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	UStaticMeshComponent* WeaponCore;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	UStaticMeshComponent* WeaponRoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	UStaticMeshComponent* WeaponHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	UBoxComponent* HitBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	UMaterialInstance* PrimaryAttackColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	UMaterialInstance* SecondaryAttackColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	UMaterialInstance* NeutralWeaponColor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
