// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Hero.h"
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

	HeroPlacer = CreateDefaultSubobject<USceneComponent>(TEXT("HeroPlacement"));
	HeroPlacer->SetupAttachment(SpringArm);

	JetPackAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("JetpackAudio"));

	MeshHolding0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshHold0"));
	MeshHolding0->SetupAttachment(HeroMesh);

	MeshHolding1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshHold1"));
	MeshHolding1->SetupAttachment(HeroMesh);

	MeshHolding2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshHold2"));
	MeshHolding2->SetupAttachment(HeroMesh);

	MeshHolding3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshHold3"));
	MeshHolding3->SetupAttachment(HeroMesh);

	MeshHolding4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshHold4"));
	MeshHolding4->SetupAttachment(HeroMesh);

	MeshHolding5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshHold5"));
	MeshHolding5->SetupAttachment(HeroMesh);


}

// Called when the game starts or when spawned
void ATowerPawn::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ATowerPawn::HeroEnters);

	HoldingMeshes.Push(MeshHolding0);
	HoldingMeshes.Push(MeshHolding1);
	HoldingMeshes.Push(MeshHolding2);
	HoldingMeshes.Push(MeshHolding3);
	HoldingMeshes.Push(MeshHolding4);
	HoldingMeshes.Push(MeshHolding5);
	
}

// Called every frame
void ATowerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeltaTimeSample = DeltaTime;

	sineInput += DeltaTime * 5;
	HeroMesh->SetRelativeLocation(FVector(
		0.f, 0.f,
		UKismetMathLibrary::Lerp(-5.f, 5.f, UKismetMathLibrary::Sin(sineInput))));


	if (SpringArm->GetRelativeLocation().Z < -490.f)
	{
		HeroMesh->SetHiddenInGame(true);
		HeroRef->SetActorLocation(HeroPlacer->GetComponentLocation());
		HeroRef->SetActorRotation(
			FRotator(
				HeroRef->GetActorRotation().Pitch, UKismetMathLibrary::FindLookAtRotation(HeroRef->GetActorLocation(), GetActorLocation()).Yaw, HeroRef->GetActorRotation().Roll));
		HeroRef->SetActorHiddenInGame(false);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(HeroRef);
		SpringArm->SetRelativeLocation(FVector(SpringArm->GetRelativeLocation().X, SpringArm->GetRelativeLocation().Y, -480));

		ToggleEnableCameraLag(false);
		JetPackAudioComp->SetVolumeMultiplier(0.f);

		if (HeroRef && HeroRef->bIsHoldingObject) {
			if(HoldingMeshes.IsValidIndex(HeroRef->PieceHoldingNow))
			{ 
				HoldingMeshes[HeroRef->PieceHoldingNow]->SetHiddenInGame(true);
				HoldingMeshes[HeroRef->PieceHoldingNow]->SetVisibility(false);
			}
		}

		TurnOffExhaust();
	}

	JetpackExhaust((WSValue == 1 || ADValue == 1) ? 1: 0);
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
	WSValue = UKismetMathLibrary::Abs(AxisValue);

	float UpdateZ = {SpringArm->GetRelativeLocation().Z + AxisValue * UpDownMultiplier};

	SpringArm->SetRelativeLocation(FVector(SpringArm->GetRelativeLocation().X, SpringArm->GetRelativeLocation().Y, UpdateZ));

	UE_LOG(LogTemp, Warning, TEXT("SpringArm Z is: %f"), SpringArm->GetRelativeLocation().Z )
}


void ATowerPawn::RotateAroundTower(float AxisValue)
{
	ADValue = UKismetMathLibrary::Abs(AxisValue);
	SpringArm->SetRelativeRotation(SpringArm->GetRelativeRotation() + FRotator(0, -AxisValue * RotateMultiplier * DeltaTimeSample, 0));
}

void ATowerPawn::HeroEnters(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->SetActorLocation(OtherActor->GetActorLocation() + (OtherActor->GetActorForwardVector() * -50));
	
	FVector TowerToPlayer = OtherActor->GetActorLocation() - GetActorLocation();

	SpringArm->SetRelativeRotation(FRotator(SpringArm->GetRelativeRotation().Pitch,TowerToPlayer.Rotation().Yaw + 180, SpringArm->GetRelativeRotation().Roll));
	ToggleEnableCameraLag(true);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(this);
	HeroMesh->SetHiddenInGame(false);
	HeroRef->SetActorHiddenInGame(true);
	JetPackAudioComp->SetVolumeMultiplier(1.f);

	if (HeroRef && HeroRef->bIsHoldingObject) {
		HoldingMeshes[HeroRef->PieceHoldingNow]->SetHiddenInGame(false);
		HoldingMeshes[HeroRef->PieceHoldingNow]->SetVisibility(true);
	}

	TurnOnExhaust();

}
