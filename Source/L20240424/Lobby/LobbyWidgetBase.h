// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class L20240424_API ULobbyWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Control")
	TObjectPtr<class UButton> StartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	TObjectPtr<class UScrollBox> ChatBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	TObjectPtr<class UTextBlock> LeftTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	TObjectPtr<class UEditableTextBox> InputBox;

	UFUNCTION()
	void OnCommitText(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnStartButton();

	void AddMessage(const FText& Text);

	void ShowStartButton();
};
