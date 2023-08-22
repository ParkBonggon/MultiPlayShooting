// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grenade.generated.h"

UCLASS()
class SHOOTINGGAMECODE_API AGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(NetMulticast, Reliable)
	void ResExplosion();

public:
	void EventExplosion();

	void ApplyGrenadeDamage();

	void PushCharacter();

	FVector CalcPushImpulse(FVector Start, FVector Target);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* Sphere;

	FTimerHandle th_Delay;
	AController* instigater;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* SoundBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* FireEffect;
};
