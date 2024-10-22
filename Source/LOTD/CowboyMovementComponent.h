// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"//Could be actor
#include "GameFramework/PawnMovementComponent.h"
#include "CowboyMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class LOTD_API UCowboyMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

	public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// Movement Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cowboy|Movement")
	float MoveSpeed = 600;
	
};
