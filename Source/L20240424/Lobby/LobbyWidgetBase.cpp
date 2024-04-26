// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidgetBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "LobbyPC.h"


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
			ALobbyPC* PC = GetOwningPlayer<ALobbyPC>();
			if (PC)
			{
				PC->C2S_SendMessage(Text);
			}
		}
		break;

	case ETextCommit::OnUserMovedFocus:
		break;

	}
}

void ULobbyWidgetBase::OnStartButton()
{
}
