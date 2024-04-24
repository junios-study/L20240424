// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"


void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	 

}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	MyPawn = Cast<ACharacter>(TryGetPawnOwner());
	if (MyPawn)
	{
		Direction = UKismetAnimationLibrary::CalculateDirection(MyPawn->GetCharacterMovement()->Velocity, MyPawn->GetControlRotation());
		Speed = MyPawn->GetCharacterMovement()->Velocity.Size2D();
		bIsFalling = MyPawn->GetCharacterMovement()->IsFalling();
	}
}
