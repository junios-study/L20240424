// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	Name = FString::Printf(TEXT("NoName %d"), FMath::RandRange(1, 100));
}
