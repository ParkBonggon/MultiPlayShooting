// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootingGameCodeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Weapon.h"
#include "ShootingplayerState.h"

//////////////////////////////////////////////////////////////////////////
// AShootingGameCodeCharacter

AShootingGameCodeCharacter::AShootingGameCodeCharacter()
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

void AShootingGameCodeCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShootingGameCodeCharacter, PlayerRotation);
	DOREPLIFETIME(AShootingGameCodeCharacter, EquipWeapon);
}

void AShootingGameCodeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AShootingGameCodeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority() == true)
	{
		PlayerRotation = GetControlRotation();
	}
}

float AShootingGameCodeCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	AShootingplayerState* ps = Cast<AShootingplayerState>(GetPlayerState());
	if (IsValid(ps) == false)
	return 0.0f;

	ps->AddDamage(DamageAmount);

	return DamageAmount;
}

void AShootingGameCodeCharacter::ReqReload_Implementation()
{
	ResReload();
}

void AShootingGameCodeCharacter::ResReload_Implementation()
{
	IWeaponInterface* InterfaceObj = Cast<IWeaponInterface>(EquipWeapon);

	if (InterfaceObj == nullptr)
		return;

	InterfaceObj->Execute_EventReload(EquipWeapon);
}

void AShootingGameCodeCharacter::ReqShoot_Implementation()
{
	ResShoot();
}

void AShootingGameCodeCharacter::ResShoot_Implementation()
{
	IWeaponInterface* InterfaceObj = Cast<IWeaponInterface>(EquipWeapon);

	if (InterfaceObj == nullptr)
		return;

	InterfaceObj->Execute_EventTrigger(EquipWeapon);
}

void AShootingGameCodeCharacter::ReqPressF_Implementation()
{
	AActor* nearestWeapon = FindNearestWeapon();

	if (IsValid(nearestWeapon) == false)
		return;

	EquipWeapon = nearestWeapon;
	EquipWeapon->SetOwner(GetController());

	OnRep_EquipWeapon();
}

void AShootingGameCodeCharacter::OnRep_EquipWeapon()
{
	bUseControllerRotationYaw = IsValid(EquipWeapon);

	IWeaponInterface* InterfaceObj = Cast<IWeaponInterface>(EquipWeapon);

	if (InterfaceObj == nullptr)
		return;

	InterfaceObj->Execute_EventPickUp(EquipWeapon, this);
}

void AShootingGameCodeCharacter::ResDrop_Implementation()
{
	IWeaponInterface* InterfaceObj = Cast<IWeaponInterface>(EquipWeapon);

	if (InterfaceObj == nullptr)
		return;

	InterfaceObj->Execute_EventDrop(EquipWeapon, this);
	
	EquipWeapon = nullptr;

	bUseControllerRotationYaw = IsValid(EquipWeapon);
}

void AShootingGameCodeCharacter::ReqDrop_Implementation()
{
	ResDrop();
}

void AShootingGameCodeCharacter::EquipTestWeapon(TSubclassOf<class AWeapon> WeaponClass)
{
	EquipWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FVector(0, 0, 0), FRotator(0, 0, 0));

	AWeapon* pWeapon = Cast<AWeapon>(EquipWeapon);
	if (IsValid(pWeapon) == false)
		return;

	pWeapon->OwnChar = this;

	EquipWeapon->AttachToComponent(GetMesh(),
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("weapon"));
}

AActor* AShootingGameCodeCharacter::FindNearestWeapon()
{
	TArray<AActor*> actors;
	GetCapsuleComponent()->GetOverlappingActors(actors, AWeapon::StaticClass());

	double nearestLength = 99999999.0f;
	AActor* nearestWeapon = nullptr;

	for (AActor* target : actors)
	{
		bool IsCanPickup = false;
		IWeaponInterface* i = Cast<IWeaponInterface>(target);
		i->Execute_IsCanPickup(target, IsCanPickup);
		if (IsCanPickup == false)
			continue;

		double distance = FVector::Dist(target->GetActorLocation(), GetActorLocation());

		if (nearestLength < distance)
			continue;

		nearestLength = distance;
		nearestWeapon = target;
	}

	return nearestWeapon;
}

FRotator AShootingGameCodeCharacter::GetPlayerRotation()
{
	ACharacter* pChar0 = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (pChar0 == this)
	{
		return GetControlRotation();
	}

	return PlayerRotation;
}

bool AShootingGameCodeCharacter::IsEquip()
{
	return IsValid(EquipWeapon);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AShootingGameCodeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShootingGameCodeCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShootingGameCodeCharacter::Look);

		//Shoot
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AShootingGameCodeCharacter::Shoot);

		//Reload
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AShootingGameCodeCharacter::Reload);

		//PressF
		EnhancedInputComponent->BindAction(PressFAction, ETriggerEvent::Started, this, &AShootingGameCodeCharacter::PressF);

		//Drop
		EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Started, this, &AShootingGameCodeCharacter::Drop);
	}

}

void AShootingGameCodeCharacter::Move(const FInputActionValue& Value)
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

void AShootingGameCodeCharacter::Look(const FInputActionValue& Value)
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

void AShootingGameCodeCharacter::Shoot(const FInputActionValue& Value)
{
	ReqShoot();
}

void AShootingGameCodeCharacter::Reload(const FInputActionValue& Value)
{
	ReqReload();
}

void AShootingGameCodeCharacter::PressF(const FInputActionValue& Value)
{
	ReqPressF();
}

void AShootingGameCodeCharacter::Drop(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Press G"));
	ReqDrop();
}




