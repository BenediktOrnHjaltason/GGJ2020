// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceBase.h"

// Sets default values
APieceBase::APieceBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = BoxCollision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void APieceBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APieceBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

