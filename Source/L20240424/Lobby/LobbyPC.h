// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPC.generated.h"

/**
 * 
 */
UCLASS()
class L20240424_API ALobbyPC : public APlayerController
{
	GENERATED_BODY()
public:

	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_SendMessage(const FText& Text); //Call
	bool C2S_SendMessage_Validate(const FText& Text); //Call
	void C2S_SendMessage_Implementation(class FText const& Text); //Execute in Server

	UFUNCTION(Client, Reliable)
	void S2C_SendMessage(const FText& Text);
	void S2C_SendMessage_Implementation(class FText const& Text); //Execute in Client
	
	//UFUNCTION(NetMulticast, Reliable)

	TObjectPtr<class ULobbyWidgetBase> LobbeyWidget;

	virtual void BeginPlay() override;
};
