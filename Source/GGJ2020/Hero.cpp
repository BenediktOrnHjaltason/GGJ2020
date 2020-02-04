// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"
#include "TowerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Block.h"
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

	MeshHolding0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshHold0"));
	MeshHolding0->SetupAttachment(RootComponent);

	MeshHolding1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshHold1"));
	MeshHolding1->SetupAttachment(RootComponent);

	MeshHolding2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshHold2"));
	MeshHolding2->SetupAttachment(RootComponent);

	MeshHolding3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshHold3"));
	MeshHolding3->SetupAttachment(RootComponent);

	MeshHolding4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshHold4"));
	MeshHolding4->SetupAttachment(RootComponent);

	MeshHolding5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshHold5"));
	MeshHolding5->SetupAttachment(RootComponent);

	PieceGrabber = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	PieceGrabber->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();
	GetTowerPawnRef();

	PieceGrabber->OnComponentBeginOverlap.AddDynamic(this, &AHero::PiecesOverlap);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AHero::BlocksOverlap);

	HoldingMeshes.Push(MeshHolding0);
	HoldingMeshes.Push(MeshHolding1);
	HoldingMeshes.Push(MeshHolding2);
	HoldingMeshes.Push(MeshHolding3);
	HoldingMeshes.Push(MeshHolding4);
	HoldingMeshes.Push(MeshHolding5);

	PieceGrabber->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
	PieceGrabber->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);



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
	PlayerInputComponent->BindAxis("RotateVertical", this, &AHero::RotateCamera);
	PlayerInputComponent->BindAction("PickUpDropDown", IE_Pressed, this, &AHero::PickupDropDown);

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

void AHero::SpawnPiece(int index) {

	if (index == 6) return;
	
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 5;

	if (index == 0) GetWorld()->SpawnActor<APieceBase>(Piece0Spawn, SpawnLocation, GetActorRotation());
	else if (index == 1) GetWorld()->SpawnActor<APieceBase>(Piece1Spawn, SpawnLocation, GetActorRotation());
	else if (index == 2) GetWorld()->SpawnActor<APieceBase>(Piece2Spawn, SpawnLocation, GetActorRotation());
	else if (index == 3) GetWorld()->SpawnActor<APieceBase>(Piece3Spawn, SpawnLocation, GetActorRotation());
	else if (index == 4) GetWorld()->SpawnActor<APieceBase>(Piece4Spawn, SpawnLocation, GetActorRotation());
	else if (index == 5) GetWorld()->SpawnActor<APieceBase>(Piece5Spawn, SpawnLocation, GetActorRotation());

}

void AHero::PiecesOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	PieceGrabber->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);

	APieceBase* Piece = Cast<APieceBase>(OtherActor);

	if(!bIsHoldingObject){
		bIsHoldingObject = true;
		if (Piece && HoldingMeshes.IsValidIndex(Piece->PieceIndex)) {
			PieceHoldingNow = Piece->PieceIndex;
		
			HoldingMeshes[PieceHoldingNow]->SetHiddenInGame(false);
			HoldingMeshes[PieceHoldingNow]->SetVisibility(true);

			Piece->Destroy();
		}
	}
}

void AHero::PickupDropDown() {

	UE_LOG(LogTemp, Warning, TEXT("PickupDropDown Called"))

	if (!bIsHoldingObject)
		PieceGrabber->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);

	else {

		HoldingMeshes[PieceHoldingNow]->SetHiddenInGame(true);
		HoldingMeshes[PieceHoldingNow]->SetVisibility(false);

		if (!bPutBlockInTower)
			SpawnPiece(PieceHoldingNow);

		else bPutBlockInTower = false;


		PieceHoldingNow = 6;

		bIsHoldingObject = false;
	}
}

void  AHero::IncrementCollectedBlocks()
{
	
}

void AHero::BlocksOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if(OtherActor->IsA(ABlock::StaticClass())) ++CollectedBlocks;
}

void AHero::RotateCamera(float AxisValue) {

	SpringArm->SetRelativeRotation(SpringArm->GetRelativeRotation() + FRotator(AxisValue, 0, 0));
}