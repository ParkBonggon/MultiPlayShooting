// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Grenade.h"
#include "ShootingGameCodeCharacter.h"

void UAnimNotify_Grenade::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AShootingGameCodeCharacter* pChar = Cast<AShootingGameCodeCharacter>(MeshComp->GetOwner());
	if (IsValid(pChar) == false)
		return;

	pChar->SpawnGrenade();
}
