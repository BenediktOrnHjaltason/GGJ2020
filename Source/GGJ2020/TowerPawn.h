// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"


#include "TowerPawn.generated.h"

UCLASS()
class GGJ2020_API ATowerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATowerPawn();

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* Collision;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* HeroMesh;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TowerMesh;

	void RotateAroundTower(float AxisValue);
	void MoveUpDown(float AxisValue);

	//------Up&Down Movement
	float sineInput{ 0 };

	//-----/

	//------Overlap

	UFUNCTION()
		void HeroEnters(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};


/* TODO:

Switch to tower when overlapping

*/