// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnPoint.h"

// Sets default values
AEnemySpawnPoint::AEnemySpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;
	Tags.Add("EnemySpawnPoint");

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Billboard"));
	Text->SetupAttachment(RootComponent);
	SetDefaultTextProperties();

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->InitCapsuleSize(42.f, 96.f);
	Collider->SetEnableGravity(false);
	Collider->SetupAttachment(RootComponent);

}

void AEnemySpawnPoint::BeginPlay()
{
	HideText();
}

void AEnemySpawnPoint::SetDefaultTextProperties()
{
	Text->Text = FText::FromString("SPAWN");
	Text->TextRenderColor = FColor::White;
	Text->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextTop);
	Text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);

	Text->SetRelativeLocation(FVector::UpVector * 50);

}

void AEnemySpawnPoint::HideText()
{
	Text->TextRenderColor = FColor::Transparent;
}

bool AEnemySpawnPoint::IsOnScreen()
{
	return false;
}