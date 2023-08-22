// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/LobbyHUD.h"
#include "Blueprint/UserWidget.h"
#include "LobbyPlayerState.h"

void ALobbyHUD::BeginPlay()
{
	Super::BeginPlay();

	check(HudWidgetClass);

	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();

	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0) == false)
		return;

	player0->SetInputMode(FInputModeUIOnly());
	player0->bShowMouseCursor = true;
}

void ALobbyHUD::BindPlayerState(ALobbyPlayerState* PlayerState)
{
	if (IsValid(PlayerState))
	{
		GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow,
			FString::Printf(TEXT("(Client)BindPlayerState userName=%s"), *PlayerState->GetUserName()));

		PlayerState->Func_Dele_UpdateUserName.AddDynamic(this, &ALobbyHUD::OnUpdateUserName);
		OnUpdateUserName(PlayerState->GetUserName());
	}
}

void ALobbyHUD::OnUpdateUserName_Implementation(const FString& userName)
{
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow,
		FString::Printf(TEXT("(Client)OnUpdateUserName userName=%s"), *userName));
}
