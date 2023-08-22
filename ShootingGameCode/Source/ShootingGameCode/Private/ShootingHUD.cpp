// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingHUD.h"
#include "Blueprint/UserWidget.h"
#include "ShootingPlayerState.h"
#include "Kismet/GameplayStatics.h"

void AShootingHUD::BeginPlay()
{
	Super::BeginPlay();

	check(HudWidgetClass);

	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();

	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0) == false)
		return;

	player0->SetInputMode(FInputModeGameOnly());
	player0->bShowMouseCursor = false;

	BindMyPlayerState();
}

void AShootingHUD::BindMyPlayerState()
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();

	if (IsValid(pc))
	{
		AShootingPlayerState* ps = Cast<AShootingPlayerState>(pc->PlayerState);
		if (IsValid(ps))
		{
			ps->Fuc_Dele_UpdateHp.AddDynamic(this, &AShootingHUD::OnUpdateMyHp);
			OnUpdateMyHp(ps->CurHp, ps->MaxHp);

			ps->Fuc_Dele_UpdateMag.AddDynamic(this, &AShootingHUD::OnUpdateMyMag);
			return;
		}
	}

	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(th_BindMyPlayerState, this, &AShootingHUD::BindMyPlayerState, 0.1f, false);
}

void AShootingHUD::BindPlayerState(AShootingPlayerState* PlayerState)
{
	if (IsValid(PlayerState))
	{
		GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow,
			FString::Printf(TEXT("(Client)BindPlayerState userName=%s"), *PlayerState->GetUserName()));

		PlayerState->Func_Dele_UpdateUserName.AddDynamic(this, &AShootingHUD::OnUpdateUserName);
		OnUpdateUserName(PlayerState->GetUserName());

		PlayerState->Fuc_Dele_UpdateKillDeath.AddDynamic(this, &AShootingHUD::OnUpdateKillDeath);
		OnUpdateKillDeath(PlayerState->GetKill(), PlayerState->GetDeath());
	}
}

void AShootingHUD::OnUpdateMyHp_Implementation(float CurHp, float MaxHp)
{
}

void AShootingHUD::OnUpdateMyAmmo_Implementation(int Ammo)
{
}

void AShootingHUD::OnUpdateMyMag_Implementation(int Mag)
{
}

void AShootingHUD::OnUpdateUserName_Implementation(const FString& userName)
{
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow,
		FString::Printf(TEXT("(Client)OnUpdateUserName userName=%s"), *userName));
}

void AShootingHUD::OnUpdateKillDeath_Implementation(int kill, int death)
{
}

void AShootingHUD::GetPlayerListSortByKill(TArray<AShootingPlayerState*>& playerStates)
{
	TArray<AActor*> arrActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShootingPlayerState::StaticClass(), arrActors);
	for (AActor* iter : arrActors)
	{
		AShootingPlayerState* pPS = Cast<AShootingPlayerState>(iter);
		if (IsValid(pPS) == false)
			continue;

		playerStates.Push(pPS);
	}

	playerStates.Sort([](const AShootingPlayerState& A, const AShootingPlayerState& B) {
		return A.Kill > B.Kill;
		});
}
