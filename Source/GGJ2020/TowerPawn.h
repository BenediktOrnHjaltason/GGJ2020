// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SceneComponent.h"


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* HeroMesh;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TowerMesh;

	UPROPERTY(EditAnyWhere)
		USceneComponent* HeroPlacer;

	UPROPERTY(VisibleAnywhere)
		UAudioComponent* JetPackAudioComp;

	UPROPERTY(VisibleAnywhere)
	USoundBase* JetpackSound;

	//--Holding Pieces

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

	TArray<UStaticMeshComponent*> HoldingMeshes;

	class AHero* HeroRef;

	FRotator HeroExitRotation;

	void RotateAroundTower(float AxisValue);
	void MoveUpDown(float AxisValue);



	//------Up&Down Movement
	float sineInput{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float fUpperLimit;

	//-----/

	//------Overlap

	UFUNCTION()
		void HeroEnters(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
		void ToggleEnableCameraLag(bool OnOrOff);

	FRotator LookDirection;

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