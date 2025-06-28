// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include <GameFramework/SpringArmComponent.h>
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

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

	UGameplayStatics::GetWorldDeltaSeconds(this);
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
	Enhanced->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::Turn);

}

void ATank::Move(const FInputActionValue& Value)
{
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector Velocity = Value.Get<FVector>().GetSafeNormal() * MoveSpeed * DeltaTime;

	AddActorLocalOffset(Velocity, true);

	FString Str = Velocity.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Move Speed : %s"), *Str);
}

void ATank::Turn(const FInputActionValue& Value)
{
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	FRotator Rotation = FRotator::ZeroRotator;

	float TurnValue = Value.Get<float>();
	Rotation.Yaw = TurnValue * TurnSpeed * DeltaTime;

	TurretMesh->AddLocalRotation(Rotation);

	FString Str = Rotation.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Turn Speed : %s"), *Str);
}
