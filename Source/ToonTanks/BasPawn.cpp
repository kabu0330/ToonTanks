// Fill out your copyright notice in the Description page of Project Settings.


#include "BasPawn.h"

// Sets default values
ABasPawn::ABasPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

