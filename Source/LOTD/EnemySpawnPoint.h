// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnemySpawnPoint.generated.h"

UCLASS()
class LOTD_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:
	AEnemySpawnPoint();

	UFUNCTION(BlueprintCallable)
	bool IsOnScreen();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* Text;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* Collider;

	void SetDefaultTextProperties();
	void HideText();
};
