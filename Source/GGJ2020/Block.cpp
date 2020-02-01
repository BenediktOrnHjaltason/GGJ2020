// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"
#include "Hero.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ABlock::PickUpOverlap);
	HeroRef = Cast<AHero>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlock::PickUpOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("Pickup Overlap"))

	++HeroRef->CollectedBlocks;
	this->Destroy();
}

