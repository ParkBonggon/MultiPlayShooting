// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineGunWeapon.h"
#include "GameFrameWork/Character.h"

void AMachineGunWeapon::EventTrigger_Implementation(bool IsPress)
{
	if (IsPress)
	{
		LoopShootMontage();
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		timerManager.SetTimer(th_loopShoot, this, &AMachineGunWeapon::LoopShootMontage, 0.2f, true);
	}
	else
	{
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		timerManager.ClearTimer(th_loopShoot);
	}
}

void AMachineGunWeapon::LoopShootMontage()
{
	if (IsValid(weaponData->ShootMontage) == false)
		return;

	OwnChar->PlayAnimMontage(weaponData->ShootMontage);
}
