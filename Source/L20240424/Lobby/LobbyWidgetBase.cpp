﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidgetBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "LobbyPC.h"
#include "Kismet/GameplayStatics.h"
#include "../MyGameInstance.h"
#include "LobbyGM.h"


void ULobbyWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &ULobbyWidgetBase::OnStartButton);
	}

	ChatBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("ChatBox")));
	LeftTime = Cast<UTextBlock>(GetWidgetFromName(TEXT("LeftTime")));
	InputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("InputBox")));

	if (InputBox)
	{
		InputBox->OnTextCommitted.AddDynamic(this, &ULobbyWidgetBase::OnCommitText);
	}
}

void ULobbyWidgetBase::OnCommitText(const FText& Text, ETextCommit::Type CommitMethod)
{
	switch (CommitMethod)
	{
		case ETextCommit::OnEnter:
		{
			UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

			ALobbyPC* PC = GetOwningPlayer<ALobbyPC>();
			if (PC && GI)
			{
				FString Temp = FString::Printf(TEXT("%s : %s"), *GI->Name, *Text.ToString());
				PC->C2S_SendMessage(FText::FromString(Temp));
				InputBox->SetText(FText::FromString(TEXT("")));
			}
		}
		break;

		case ETextCommit::OnCleared:
		{
			InputBox->SetUserFocus(GetOwningPlayer());
		}
		break;
	}
}

void ULobbyWidgetBase::OnStartButton()
{
	ALobbyGM* GM = Cast<ALobbyGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->StartGame();
	}
}

void ULobbyWidgetBase::AddMessage(const FText& Text)
{
	TObjectPtr<UTextBlock> NewMessage = NewObject<UTextBlock>(ChatBox);
	if (NewMessage)
	{
		NewMessage->SetText(Text);
		FSlateFontInfo FontInfo = NewMessage->GetFont();
		FontInfo.Size = 18;
		NewMessage->SetFont(FontInfo);

		ChatBox->AddChild(NewMessage);
		ChatBox->ScrollToEnd();
	}
}

void ULobbyWidgetBase::ShowStartButton()
{
	if (StartButton)
	{
		StartButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void ULobbyWidgetBase::UpdateLeftTime(int32 NewLeftTime)
{
	FString Temp = FString::Printf(TEXT("%d초 남았습니다."), NewLeftTime);
	LeftTime->SetText(FText::FromString(Temp));
}
