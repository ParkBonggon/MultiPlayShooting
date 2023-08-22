// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LobbyHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAMECODE_API ALobbyHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	void BindPlayerState(class ALobbyPlayerState* PlayerState);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateUserName(const FString& userName);

	void OnUpdateUserName_Implementation(const FString& userName);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> HudWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* HudWidget;
};
