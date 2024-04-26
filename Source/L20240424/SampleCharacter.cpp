// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASampleCharacter::ASampleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		FRotator(0, -90.0f, 0)
	);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ASampleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASampleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASampleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UIC)
	{
		UIC->BindAction(LookAction, ETriggerEvent::Triggered, this,
			&ASampleCharacter::Look);

		UIC->BindAction(MoveAction, ETriggerEvent::Triggered, this,
			&ASampleCharacter::Move);

		UIC->BindAction(JumpAction, ETriggerEvent::Triggered, this,
			&ASampleCharacter::Jump);

		UIC->BindAction(FireAction, ETriggerEvent::Triggered, this,
			&ASampleCharacter::Fire);
	}


}

void ASampleCharacter::Look(const FInputActionValue& Value)
{
	FVector2D Data = Value.Get<FVector2D>();

	AddControllerYawInput(Data.X);
	AddControllerPitchInput(Data.Y);

}

void ASampleCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Data = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator ForwordRotation = FRotator(0, Rotation.Yaw, 0);
	const FVector ForwordVector = UKismetMathLibrary::GetForwardVector(ForwordRotation);
	const FVector RightVector = UKismetMathLibrary::GetRightVector(ForwordRotation);


	AddMovementInput(ForwordVector, Data.Y);
	AddMovementInput(RightVector, Data.X);
}

void ASampleCharacter::Fire(const FInputActionValue& Value)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		int32 ScreenX;
		int32 ScreenY;
		
		FVector CrosshairWorldPosition;
		FVector CrosshairWorldDirection;

		PC->GetViewportSize(ScreenX, ScreenY);

		PC->DeprojectScreenPositionToWorld(ScreenX / 2, ScreenY / 2,
			CrosshairWorldPosition, CrosshairWorldDirection);

		FVector StartPosition = CrosshairWorldPosition;
		FVector EndPosition = CrosshairWorldPosition + (CrosshairWorldDirection * 100000);

		TArray<TEnumAsByte<EObjectTypeQuery>> Objects;

		Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
		Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
		Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
		//Objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

		TArray<AActor*> IgnoreActors;
		IgnoreActors.Add(this);

		FHitResult OutHit;
		bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
			GetWorld(),
			StartPosition,
			EndPosition,
			Objects,
			true,
			IgnoreActors,
			EDrawDebugTrace::ForDuration,
			OutHit,
			true,
			FLinearColor::Red,
			FLinearColor::Green,
			5.0f);
	}
}

