// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShootingHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAMECODE_API AShootingHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

public:
	void BindMyPlayerState();

	void BindPlayerState(class AShootingPlayerState* PlayerState);

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateMyHp(float CurHp, float MaxHp);

	void OnUpdateMyHp_Implementation(float CurHp, float MaxHp);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateMyAmmo(int Ammo);

	void OnUpdateMyAmmo_Implementation(int Ammo);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateMyMag(int Mag);

	void OnUpdateMyMag_Implementation(int Mag);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateUserName(const FString& userName);

	void OnUpdateUserName_Implementation(const FString& userName);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateKillDeath(int kill, int death);

	void OnUpdateKillDeath_Implementation(int kill, int death);

public:
	UFUNCTION(BlueprintPure)
	void GetPlayerListSortByKill(TArray<AShootingPlayerState*>& playerStates);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> HudWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* HudWidget;

	FTimerHandle th_BindMyPlayerState;
};
