// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingPlayerController.h"
#include "ShootingGameInstance.h"
#include "ShootingPlayerState.h"

AShootingPlayerController::AShootingPlayerController()
{
}

void AShootingPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow,
		TEXT("(Server)OnPossess"));

	ResClientPossess();
}

void AShootingPlayerController::ResClientPossess_Implementation()
{
	UShootingGameInstance* GameInst = Cast<UShootingGameInstance>(GetGameInstance());
	if (GameInst == nullptr)
		return;

	FString Name = GameInst->GetUserName();


	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow,
		FString::Printf(TEXT("(Client)ResClientPossess Name=%s"), *Name));

	ReqChangeUserName(Name);
}

void AShootingPlayerController::ReqChangeUserName_Implementation(const FString& NewName)
{
	AShootingPlayerState* ps = Cast<AShootingPlayerState>(PlayerState);
	if (ps == nullptr)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow,
		FString::Printf(TEXT("(Server)ReqChangeUserName Name=%s"), *NewName));

	ps->SetUserName(NewName);
}


