// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingHUD.h"
#include "Blueprint/UserWidget.h"
#include "ShootingplayerState.h"

void AShootingHUD::BeginPlay()
{
	Super::BeginPlay();

	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();

	BindMyPlayerState();
}

//HP Àç±ÍÇÔ¼ö
void AShootingHUD::BindMyPlayerState()
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();

	if (IsValid(pc))
	{
		AShootingplayerState* ps = Cast<AShootingplayerState>(pc->PlayerState);
		if (IsValid(ps))
		{
			ps->Fuc_Dele_UpdateHP.AddDynamic(this, &AShootingHUD::OnUpdateMyHP);
			OnUpdateMyHP(ps->CurHP, ps->MaxHP);

			ps->Fuc_Dele_UpdateMag.AddDynamic(this, &AShootingHUD::OnUpdateMyMag);

			return;
		}
	}

	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(th_BindMyPlayerState, this, &AShootingHUD::BindMyPlayerState, 0.1f, false);
}

void AShootingHUD::OnUpdateMyHP_Implementation(float CurHP, float MaxHP)
{
}

void AShootingHUD::OnUpdateMyAmmo_Implementation(int Ammo)
{

}

void AShootingHUD::OnUpdateMyMag_Implementation(int Mag)
{
}
