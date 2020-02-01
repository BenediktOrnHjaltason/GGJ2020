// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATowerPawn::ATowerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Collision;

	TowerMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("TowerMesh"));
	TowerMesh->SetupAttachment(Collision);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Collision);

	HeroMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeroMesh"));
	HeroMesh->SetupAttachment(SpringArm);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(HeroMesh);

}

// Called when the game starts or when spawned
void ATowerPawn::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ATowerPawn::HeroEnters);
	
}

// Called every frame
void ATowerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	sineInput += DeltaTime * 3;

	HeroMesh->SetRelativeLocation(FVector(
		0.f, 0.f,
		UKismetMathLibrary::Lerp(-4.f, 4.f, UKismetMathLibrary::Sin(sineInput))));

}

// Called to bind functionality to input
void ATowerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("ForwardBackward", this, &ATowerPawn::MoveUpDown);
	PlayerInputComponent->BindAxis("RightLeft", this, &ATowerPawn::RotateAroundTower);

}

void ATowerPawn::MoveUpDown(float AxisValue)
{
	UE_LOG(LogTemp, Warning, TEXT("MoveUpDownCalled"))
	SpringArm->SetRelativeLocation(SpringArm->GetRelativeLocation() + FVector(0, 0, AxisValue * 15));
}

void ATowerPawn::RotateAroundTower(float AxisValue)
{
	SpringArm->SetRelativeRotation(SpringArm->GetRelativeRotation() + FRotator(0, -AxisValue * 3, 0));
}

void ATowerPawn::HeroEnters(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->SetActorLocation(OtherActor->GetActorLocation() + (OtherActor->GetActorForwardVector() * -50));

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(this);
	HeroMesh->SetHiddenInGame(false);
}
