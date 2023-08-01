// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingplayerState.h"
#include "Net/UnrealNetwork.h"

AShootingplayerState::AShootingplayerState()
{
	CurHP = 100;
	MaxHP = 100;
	Mag = 0;
}

void AShootingplayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShootingplayerState, CurHP);
	DOREPLIFETIME(AShootingplayerState, MaxHP);
	DOREPLIFETIME(AShootingplayerState, Mag);

}

void AShootingplayerState::OnRep_CurHP()
{
	if (Fuc_Dele_UpdateHP.IsBound())
	{
		Fuc_Dele_UpdateHP.Broadcast(CurHP, MaxHP);
	}
}

void AShootingplayerState::OnRep_MaxHP()
{
}

void AShootingplayerState::OnRep_Mag()
{
	if (Fuc_Dele_UpdateMag.IsBound())
	{
		Fuc_Dele_UpdateMag.Broadcast(Mag);
	}
}

void AShootingplayerState::AddDamage(float Damage)
{
	CurHP = CurHP - Damage;

	OnRep_CurHP();
}

void AShootingplayerState::AddMag()
{
	Mag = Mag + 1;

	OnRep_Mag();
}
