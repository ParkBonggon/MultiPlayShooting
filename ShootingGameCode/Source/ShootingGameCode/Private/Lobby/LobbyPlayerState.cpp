// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/LobbyPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "LobbyHUD.h"

ALobbyPlayerState::ALobbyPlayerState()
{
}

void ALobbyPlayerState::BeginPlay()
{
	Super::BeginPlay();

	UpdateBind();
}

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyPlayerState, UserName);
}

void ALobbyPlayerState::OnRep_UserName()
{
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow,
		FString::Printf(TEXT("(Client)OnRep_UserName UserName=%s"), *UserName));

	if (Func_Dele_UpdateUserName.IsBound())
		Func_Dele_UpdateUserName.Broadcast(UserName);
}

void ALobbyPlayerState::SetUserName(const FString& NewName)
{
	UserName = NewName;

	OnRep_UserName();
}

void ALobbyPlayerState::UpdateBind()
{
	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (player0)
	{
		ALobbyHUD* pHud = Cast<ALobbyHUD>(player0->GetHUD());
		if (pHud)
		{
			pHud->BindPlayerState(this);
			return;
		}
	}

	FTimerManager& TimerMgr = GetWorldTimerManager();
	TimerMgr.SetTimer(th_UpdateBind, this, &ALobbyPlayerState::UpdateBind, 0.1f, false);
}
