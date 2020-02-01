// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
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

	void ForwardBackward(float AxisValue);
	void MoveRightLeft(float AxisValue);
	void RotatePlayer(float AxisValue);



	class ATowerPawn* TowerPawnRef;
	void GetTowerPawnRef();

	UFUNCTION(BlueprintCallable)
		int detectShape(bool p0, bool p1, bool p2, bool p3, bool p4, bool p5);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
