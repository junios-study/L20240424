// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class L20240424_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	TObjectPtr<class ACharacter> MyPawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "stat")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "stat")
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "stat")
	bool bIsFalling;
};
