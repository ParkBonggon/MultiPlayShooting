// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingHUD.h"
#include "Blueprint/UserWidget.h"

void AShootingHUD::BeginPlay()
{
	Super::BeginPlay();

	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();
}
