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
		TowerPawn->HeroRef = this;
	}
}

int AHero::detectShape(bool p0, bool p1, bool p2, bool p3, bool p4, bool p5)
{
	if (p0 == true && p1 == false && p2 == false && p3 == true && p4 == true && p5 == true) return 0;
	if (p0 == false && p1 == false && p2 == true && p3 == true && p4 == true && p5 == true) return 1;

	if ((p0 == true && p1 == true && p2 == false && p3 == true && p4 == true && p5 == false) ||
		(p0 == false && p1 == true && p2 == true && p3 == false && p4 == true && p5 == true))
	{
		if (p0 == true && p1 == true && p2 == false && p3 == true && p4 == true && p5 == false)	return 9;
		if (p0 == false && p1 == true && p2 == true && p3 == false && p4 == true && p5 == true) return 10;

	}


	if (p0 == false && p1 == true && p2 == true && p3 == true && p4 == true && p5 == false) return 3;
	if (p0 == false && p1 == true && p2 == false && p3 == true && p4 == true && p5 == true) return 4;
	if (p0 == true && p1 == true && p2 == false && p3 == false && p4 == true && p5 == true) return 5;

	else return 6;
}