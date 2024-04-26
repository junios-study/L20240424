// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class L20240424_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Data", Replicated)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Data", ReplicatedUsing="OnRep_LeftTime")
	int32 LeftTime = 60;

	UFUNCTION()
	void OnRep_LeftTime(); // Not Call Server

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};

