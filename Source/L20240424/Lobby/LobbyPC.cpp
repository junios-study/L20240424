// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPC.h"
#include "LobbyWidgetBase.h"

bool ALobbyPC::C2S_SendMessage_Validate(const FText& Text)
{
	return true;
}

void ALobbyPC::C2S_SendMessage_Implementation(FText const& Text)
{
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		ALobbyPC* PC = Cast<ALobbyPC>(*Iter);
		if (PC)
		{
			PC->S2C_SendMessage(Text);
		}
	}
}

void ALobbyPC::S2C_SendMessage_Implementation(FText const& Text)
{
	//UE_LOG(LogTemp, Warning, TEXT("Reiceve %s"), *Text.ToString());
	if (LobbeyWidget)
	{
		LobbeyWidget->AddMessage(Text);
	}
}

void ALobbyPC::BeginPlay()
{
	Super::BeginPlay();

	//Path
	FSoftClassPath LobbyWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WB_Lobby.WB_Lobby_C'"));

	//#include 
	TObjectPtr<UClass> WidgetClass = LobbyWidgetClass.TryLoadClass<ULobbyWidgetBase>();

	if (WidgetClass)
	{
		if (IsLocalPlayerController())
		{
			LobbeyWidget = CreateWidget<ULobbyWidgetBase>(this, WidgetClass);
			LobbeyWidget->AddToViewport();
			if (HasAuthority())
			{
				LobbeyWidget->ShowStartButton();
			}

			SetInputMode(FInputModeUIOnly());
			bShowMouseCursor = true;
		}
	}
}
