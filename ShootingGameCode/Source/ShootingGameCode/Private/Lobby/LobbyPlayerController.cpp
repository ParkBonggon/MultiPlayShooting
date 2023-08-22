// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/LobbyPlayerController.h"
#include "ShootingGameInstance.h"
#include "LobbyPlayerState.h"

ALobbyPlayerController::ALobbyPlayerController()
{
}

void ALobbyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow,
		TEXT("(Server)OnPossess"));

	ResClientPossess();
}

void ALobbyPlayerController::ResClientPossess_Implementation()
{
	UShootingGameInstance* GameInst = Cast<UShootingGameInstance>(GetGameInstance());
	if (GameInst == nullptr)
		return;

	FString Name = GameInst->GetUserName();


	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow,
		FString::Printf(TEXT("(Client)ResClientPossess Name=%s"), *Name));

	ReqChangeUserName(Name);
}

void ALobbyPlayerController::ReqChangeUserName_Implementation(const FString& NewName)
{
	ALobbyPlayerState* ps = Cast<ALobbyPlayerState>(PlayerState);
	if (ps == nullptr)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow,
		FString::Printf(TEXT("(Server)ReqChangeUserName Name=%s"), *NewName));

	ps->SetUserName(NewName);
}

