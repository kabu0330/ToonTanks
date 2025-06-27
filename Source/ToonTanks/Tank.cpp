// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include <GameFramework/SpringArmComponent.h>
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"

ATank::ATank()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
}

ATank::~ATank()
{
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Enhanced = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	Enhanced->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);

}

void ATank::Move(const FInputActionValue& Value)
{
	FString Str = Value.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Value : %s"), *Str);
}