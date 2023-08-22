// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_Lobby_UserName, const FString&, UserName);
/**
 * 
 */
UCLASS()
class SHOOTINGGAMECODE_API ALobbyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ALobbyPlayerState();

public:
	virtual void BeginPlay() override;

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
	FDele_Lobby_UserName Func_Dele_UpdateUserName;

private:
	UPROPERTY(ReplicatedUsing = OnRep_UserName)
	FString UserName;

	FTimerHandle th_UpdateBind;
};
