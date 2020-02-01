// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"
#include "TowerPawn.h"
#include "EngineUtils.h"

// Sets default values
AHero::AHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();
	GetTowerPawnRef();
}

// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("ForwardBackward", this, &AHero::ForwardBackward);
	PlayerInputComponent->BindAxis("RightLeft", this, &AHero::MoveRightLeft);
	PlayerInputComponent->BindAxis("Rotate", this, &AHero::RotatePlayer);

}

void AHero::ForwardBackward(float AxisValue) {
	AddMovementInput(GetActorForwardVector(), AxisValue);
}
void AHero::MoveRightLeft(float AxisValue) {
	AddMovementInput(GetActorRightVector(), AxisValue);
}
void AHero::RotatePlayer(float AxisValue) {
	AddControllerYawInput(AxisValue);
}

void AHero::GetTowerPawnRef()
{
	for (TActorIterator<ATowerPawn> TowerPawnIt(GetWorld()); TowerPawnIt; ++TowerPawnIt)
	{
		ATowerPawn* TowerPawn = *TowerPawnIt;

		TowerPawnRef = TowerPawn;
	}
}

