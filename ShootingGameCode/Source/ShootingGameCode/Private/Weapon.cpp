// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	WeaponMesh->SetCollisionProfileName("weapon");
	WeaponMesh->SetSimulatePhysics(true);

	bReplicates = true;
	SetReplicateMovement(true);

	SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::EventTrigger_Implementation()
{
	if (IsValid(ShootMontage) == false)
		return;

	OwnChar->PlayAnimMontage(ShootMontage);
}

void AWeapon::EventReload_Implementation()
{
	if (IsValid(ReloadMontage) == false)
		return;

	OwnChar->PlayAnimMontage(ReloadMontage);
}

void AWeapon::EventShoot_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShootEffect,
		WeaponMesh->GetSocketLocation("muzzle"),
		WeaponMesh->GetSocketRotation("muzzle"), 
		FVector(0.1f, 0.1f, 0.1f));

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ShootSound,
		WeaponMesh->GetSocketLocation("muzzle"));

	APlayerController* Shooter = GetWorld()->GetFirstPlayerController();


	FVector CameraLoc = Shooter->PlayerCameraManager->GetCameraLocation();
	FVector CameraForward = Shooter->PlayerCameraManager->GetActorForwardVector();
	FVector Start = (CameraForward * GetFireStartLength()) + CameraLoc;
	FVector End = (CameraForward * 5000.0f) + CameraLoc;
	
	ReqShoot(Start, End);
}

void AWeapon::EventPickUp_Implementation(ACharacter* targetChar)
{
	OwnChar = targetChar;

	WeaponMesh->SetSimulatePhysics(false);

	AttachToComponent(targetChar->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("weapon"));
}

void AWeapon::EventDrop_Implementation(ACharacter* targetChar)
{
	OwnChar = nullptr;

	WeaponMesh->SetSimulatePhysics(true);

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void AWeapon::IsCanPickup_Implementation(bool& IsCanPickup)
{
	if (OwnChar != nullptr)
	{
		IsCanPickup = false; 
		return;
	}
	IsCanPickup = true;
}

void AWeapon::ReqShoot_Implementation(FVector vStart, FVector vEnd)
{
	FHitResult result;
	FCollisionObjectQueryParams collisionObjectQuery;

	collisionObjectQuery.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	collisionObjectQuery.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	collisionObjectQuery.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	collisionObjectQuery.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);
	collisionObjectQuery.AddObjectTypesToQuery(ECollisionChannel::ECC_Vehicle);
	collisionObjectQuery.AddObjectTypesToQuery(ECollisionChannel::ECC_Destructible);

	FCollisionQueryParams collisionQuery;
	collisionQuery.AddIgnoredActor(OwnChar);

	GetWorld()->LineTraceSingleByObjectType(result, vStart, vEnd, collisionObjectQuery, collisionQuery);
	DrawDebugLine(GetWorld(), vStart, vEnd, FColor::Green, false, 5.0f);
}

float AWeapon::GetFireStartLength()
{
	if (IsValid(OwnChar) == false)
	return 0.0f;

	USpringArmComponent* Arm = Cast<USpringArmComponent>(OwnChar->GetComponentByClass(USpringArmComponent::StaticClass()));
	if (IsValid(Arm) == false)
	return 0.0f;

	return Arm->TargetArmLength + 100;
}

