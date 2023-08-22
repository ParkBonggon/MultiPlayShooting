// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShootingPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDele_UpdateHp_TwoParams, float, CurHp, float, MaxHp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_UpdateMag_OneParam, int, Mag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_Shooting_UserName, const FString&, UserName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDele_UpdateKillDeath_TwoParams, int, Kill, int, Death);
/**
 * 
 */
UCLASS()
class SHOOTINGGAMECODE_API AShootingPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AShootingPlayerState();

public:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnRep_CurHp();

	UFUNCTION()
	void OnRep_MaxHp();

	UFUNCTION()
	void OnRep_Mag();

	UFUNCTION()
	void OnRep_Kill();

	UFUNCTION()
	void OnRep_Death();

public:
	UFUNCTION(BlueprintCallable)
	bool AddDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void AddMag();

	UFUNCTION(BlueprintCallable)
	bool UseMag();

	UFUNCTION(BlueprintPure)
	bool IsCanUseMag();

	UFUNCTION(BlueprintCallable)
	void AddHeal(float Heal);

	UFUNCTION(BlueprintCallable)
	void AddKill();

	UFUNCTION(BlueprintCallable)
	void AddDeath();

public:
	UPROPERTY(ReplicatedUsing = OnRep_CurHp)
	float CurHp;

	UPROPERTY(ReplicatedUsing = OnRep_MaxHp)
	float MaxHp;

	UPROPERTY(ReplicatedUsing = OnRep_Mag)
	int Mag;

	UFUNCTION(BlueprintPure)
	int GetKill() { return Kill; };

	UFUNCTION(BlueprintPure)
	int GetDeath() { return Death; };

	UPROPERTY(ReplicatedUsing = OnRep_Kill)
	int Kill;

	UPROPERTY(ReplicatedUsing = OnRep_Death)
	int Death;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateHp_TwoParams Fuc_Dele_UpdateHp;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateMag_OneParam Fuc_Dele_UpdateMag;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateKillDeath_TwoParams Fuc_Dele_UpdateKillDeath;

public:
	UFUNCTION()
	void OnRep_UserName();

	UFUNCTION(BlueprintCallable)
	void SetUserName(const FString& NewName);

	UFUNCTION(BlueprintPure)
	FString GetUserName() { return UserName; };

	void UpdateBind();

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_Shooting_UserName Func_Dele_UpdateUserName;

private:
	UPROPERTY(ReplicatedUsing = OnRep_UserName)
	FString UserName;

	FTimerHandle th_UpdateBind;
};
