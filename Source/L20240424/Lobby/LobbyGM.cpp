// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGM.h"
#include "../MyGameStateBase.h"

void ALobbyGM::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	//ErrorMessage = TEXT("GetOut");
}

APlayerController* ALobbyGM::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{

	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

}

void ALobbyGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ALobbyGM::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		LobbyTimer,
		this,
		&ALobbyGM::DecreaseTime,
		1.0f,
		true,
		1.0f
	);

	
}

void ALobbyGM::DecreaseTime()
{
	AMyGameStateBase* GS = GetGameState<AMyGameStateBase>();
	if (GS)
	{
		GS->LeftTime--;
		GS->OnRep_LeftTime();//Only Server
		if (GS->LeftTime < 0)
		{
			GetWorldTimerManager().ClearTimer(LobbyTimer);
			GS->LeftTime = 0;
			StartGame();
		}
	}
}

void ALobbyGM::StartGame()
{
	GetWorld()->ServerTravel(TEXT("InGame"));
}
