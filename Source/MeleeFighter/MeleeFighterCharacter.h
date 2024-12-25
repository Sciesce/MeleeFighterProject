// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MeleeFighterCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AMeleeFighterCharacter : public ACharacter
{
	GENERATED_BODY()

	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;
	
public:
	AMeleeFighterCharacter();

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Endurance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bAttacking;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	int32 AttackIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	TArray<UAnimMontage*> AttackAnimations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	UAnimMontage* CurrentAttackAnim;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	FTimerHandle T_AttackProgression;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	float LastHitRecoveryDelay;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	float ResetAttackSequenceDelay;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	float AdvanceAttackDelay;
	
	//Functions

	UFUNCTION(BlueprintNativeEvent, Category = "Combat")
	void ResetAttacks();

	UFUNCTION(BlueprintNativeEvent, Category = "Combat")
	void ResetAttackSequence();

	UFUNCTION(BlueprintNativeEvent, Category = "Combat")
	void AdvanceAttack();

	UFUNCTION(Category = "Combat")
	void ResetAttack();
	
private:
	//doOnce bools
	bool AttackDoOnce;
	
	//timer handles
	FTimerHandle ResetAttackTimerHandle;	
	FTimerHandle AdvanceAttackTimerHandle;	
	FTimerHandle ResetAttackSequenceTimerHandle;;	
	
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for attack input */
	void Attack(const FInputActionValue& Value);
	void StopAttack(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
