// Copyright Epic Games, Inc. All Rights Reserved.

#include "MeleeFighterCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AMeleeFighterCharacter

AMeleeFighterCharacter::AMeleeFighterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AMeleeFighterCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	
	//Add Input Mapping Context
	if (PlayerController != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	SetupPlayerInputComponent(PlayerController->InputComponent);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMeleeFighterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMeleeFighterCharacter::Move);
	
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMeleeFighterCharacter::Look);
	
		// Attacking
		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Started, this, &AMeleeFighterCharacter::PrimaryAttack);
		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Completed, this, &AMeleeFighterCharacter::StopAttack);

		EnhancedInputComponent->BindAction(SecondaryAttackAction, ETriggerEvent::Started, this, &AMeleeFighterCharacter::SecondaryAttack);
		EnhancedInputComponent->BindAction(SecondaryAttackAction, ETriggerEvent::Completed, this, &AMeleeFighterCharacter::StopAttack);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMeleeFighterCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMeleeFighterCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMeleeFighterCharacter::PrimaryAttack(const FInputActionValue& Value)
{
	bPrimaryAttack = true;
	AMeleeFighterCharacter::HandleAttack(Value);
}

void AMeleeFighterCharacter::SecondaryAttack(const FInputActionValue& Value)
{
	bPrimaryAttack = false;
	AMeleeFighterCharacter::HandleAttack(Value);
}

void AMeleeFighterCharacter::HandleAttack(const FInputActionValue& Value)
{
	if (AttackDoOnce) //preventing double trigger, resets on release/complete
	{
		return;
	}
	AttackDoOnce = true;

	if (bAttacking && AttackAnimations.Num() - 1 != AttackIndex) //interrupt attack animation / sequence if not on final attack
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Stopping attack"));  //debug to verify primary attack is happening

		//resetting any combo progression
		if(T_AttackProgression.IsValid())
		{
			GetWorldTimerManager().ClearTimer(T_AttackProgression);
		}

		//interrupting anim
		StopAnimMontage(CurrentAttackAnim);

		//if attack reset timer is not valid, initiate timer
		if (!GetWorld()->GetTimerManager().IsTimerActive(T_ResetAttack))
		{
			AMeleeFighterCharacter::ResetAttacks_Implementation();			
		}
		return;
	}
	else
	{
		if (AttackAnimations.IsValidIndex(AttackIndex) && !FinalHitDoOnce)  //verification that index is valid before attempting to attack
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Attacking"));  //debug to verify primary attack is happening

			if (AttackAnimations.Num() -1 == AttackIndex)
			{
				FinalHitDoOnce = true;
				if(!GetWorld()->GetTimerManager().IsTimerActive(T_ResetFinalHitDoOnce))
				{
					GetWorld()->GetTimerManager().SetTimer(T_ResetFinalHitDoOnce, this, &AMeleeFighterCharacter::ResetFinalHitDoOnce, ResetAttackIndexDelay, false);
				}
			}	
			bAttacking = true;
	
			if(bPrimaryAttack)
			{
				CurrentAttackAnim = AttackAnimations[AttackIndex];
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Primary Attack"));
			}
			else
			{
				CurrentAttackAnim = SecondaryAttackAnimations[AttackIndex];
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Secondary Attack"));
			}

			//playing selected animation
			PlayAnimMontage(CurrentAttackAnim);
			
			//Timers to reset sequence and advance combo
			GetWorld()->GetTimerManager().SetTimer(T_ResetAttackIndex, this, &AMeleeFighterCharacter::ResetAttackIndex_Implementation, ResetAttackIndexDelay,false);
			GetWorld()->GetTimerManager().SetTimer(T_AttackProgression, this, &AMeleeFighterCharacter::AdvanceAttack_Implementation, AdvanceAttackDelay, false);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Index Invalid"));
		}
	}
}

void AMeleeFighterCharacter::StopAttack(const FInputActionValue& Value)  //Resetting do once
{
	AttackDoOnce = false;
}

void AMeleeFighterCharacter::AdvanceAttack_Implementation()  //cycling through attack anims
{
	if(AttackIndex < AttackAnimations.Num() - 1 )
	{
		AttackIndex ++;
		bAttacking = false;
	}
	else
	{
		ResetAttacks_Implementation();
	}
	
}

void AMeleeFighterCharacter::ResetAttacks_Implementation()
{
	//ResetAttackSequence_Implementation();
	//timer to reset attack bool
	if(GetWorld()->GetTimerManager().IsTimerActive(T_ResetAttack))
	{
		GetWorld()->GetTimerManager().ClearTimer(T_ResetAttack);
	}
	GetWorld()->GetTimerManager().SetTimer(T_ResetAttack, this, &AMeleeFighterCharacter::ResetAttack, LastHitRecoveryDelay, false);
}

void AMeleeFighterCharacter::ResetAttackIndex_Implementation()
{
	AttackIndex = 0;
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Index Reset"));
}

void AMeleeFighterCharacter::ResetAttack()
{
	bAttacking = false;
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Attack reset"));
}



void AMeleeFighterCharacter::ResetFinalHitDoOnce()
{
	FinalHitDoOnce = false;
}
