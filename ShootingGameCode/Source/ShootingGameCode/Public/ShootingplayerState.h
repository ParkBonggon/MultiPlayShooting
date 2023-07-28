// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShootingplayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDele_UpdateHp_TwoParams, float, CurHP, float, MaxHP);
/**
 * 
 */
UCLASS()
class SHOOTINGGAMECODE_API AShootingplayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AShootingplayerState();

public:
	UFUNCTION()
	void OnRep_CurHP();

	UFUNCTION()
	void OnRep_MaxHP();

	UFUNCTION(BlueprintCallable)
	void AddDamage(float Damage);

public:
	UPROPERTY(ReplicatedUsing = OnRep_CurHP)
	float CurHP;

	UPROPERTY(ReplicatedUsing = OnRep_MaxHP)
	float MaxHP;
	
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateHp_TwoParams Fuc_Dele_UpdateHP;
};
