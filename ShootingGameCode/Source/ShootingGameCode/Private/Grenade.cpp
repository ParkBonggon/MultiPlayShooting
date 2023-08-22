// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetSimulatePhysics(true);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);
	Sphere->SetSphereRadius(400.0f);

	bReplicates = true;
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority() == false)
		return;

	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(th_Delay, this, &AGrenade::EventExplosion, 5.0f, false);
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrenade::ResExplosion_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireEffect,
		Sphere->GetComponentTransform());

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase,
		Sphere->GetComponentLocation());

	Destroy();
}

void AGrenade::EventExplosion()
{
	ApplyGrenadeDamage();

	ResExplosion();
}

void AGrenade::ApplyGrenadeDamage()
{
	FVector Origin = Sphere->GetComponentLocation();
	float innerRadius = Sphere->GetScaledSphereRadius() * 0.2f;
	float OuterRadius = Sphere->GetScaledSphereRadius();
	float DamageFalloff = 0.1f;
	TArray<AActor*> ignoreActor;

	UGameplayStatics::ApplyRadialDamageWithFalloff(
		GetWorld(), 100, 10,
		Origin,	innerRadius,OuterRadius,
		DamageFalloff, UDamageType::StaticClass(),
		ignoreActor, this, instigater
	);

	PushCharacter();
}

void AGrenade::PushCharacter()
{
	TArray<AActor*> OverlapActors;
	Sphere->GetOverlappingActors(OverlapActors, ACharacter::StaticClass());

	for (AActor* target : OverlapActors)
	{
		ACharacter* pChar = Cast<ACharacter>(target);
		if (IsValid(pChar) == false)
			continue;

		FVector vStart = Sphere->GetComponentLocation();;
		FVector vTarget = target->GetActorLocation();

		pChar->GetCharacterMovement()->AddImpulse(CalcPushImpulse(vStart, vTarget));
	}
}

FVector AGrenade::CalcPushImpulse(FVector Start, FVector Target)
{
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(Start, Target);
	FVector fowardVec = rot.Vector();

	float Distance = FVector::Distance(Start, Target);
	float Dis_per = Distance / Sphere->GetScaledSphereRadius();
	float reDis_per = 1.0f - Dis_per;
	float velocity = reDis_per * 200000.0f;
	FVector impulse = fowardVec * velocity;

	return impulse;
}

