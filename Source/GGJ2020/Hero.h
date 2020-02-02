// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PieceBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Hero.generated.h"

UCLASS()
class GGJ2020_API AHero : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHero();

	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CollectedBlocks{ 4 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PieceIndexToSpawn{ 0 };

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshHolding0;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshHolding1;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshHolding2;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshHolding3;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshHolding4;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshHolding5;

	UPROPERTY(EditAnywhere)
		USphereComponent* PieceGrabber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPutBlockInTower{ false };

	UFUNCTION()
		void PiecesOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	TArray<UStaticMeshComponent*> HoldingMeshes;

	


	
	void ForwardBackward(float AxisValue);
	void MoveRightLeft(float AxisValue);
	void RotatePlayer(float AxisValue);




	class ATowerPawn* TowerPawnRef;
	void GetTowerPawnRef();

	UPROPERTY(EditAnyWhere)
		TSubclassOf<APieceBase> Piece0Spawn;

	UPROPERTY(EditAnyWhere)
		TSubclassOf<APieceBase> Piece1Spawn;

	UPROPERTY(EditAnyWhere)
		TSubclassOf<APieceBase> Piece2Spawn;

	UPROPERTY(EditAnyWhere)
		TSubclassOf<APieceBase> Piece3Spawn;

	UPROPERTY(EditAnyWhere)
		TSubclassOf<APieceBase> Piece4Spawn;

	UPROPERTY(EditAnyWhere)
		TSubclassOf<APieceBase> Piece5Spawn;

	UFUNCTION(BlueprintCallable)
		void SpawnPiece(int index);



	UFUNCTION(BlueprintCallable)
		int detectShape(bool p0, bool p1, bool p2, bool p3, bool p4, bool p5);


	//No 6 became default for NOTHING
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PieceHoldingNow{ 6 };

	bool bIsHoldingObject = false;

	UFUNCTION(BlueprintCallable)
	void PickupDropDown();
		



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
