// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Lobby/LobbyPC.h"
#include "Lobby/LobbyWidgetBase.h"

void AMyGameStateBase::OnRep_LeftTime()
{
	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->LobbeyWidget->UpdateLeftTime(LeftTime);
	}
}

void AMyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyGameStateBase, LeftTime);
}
