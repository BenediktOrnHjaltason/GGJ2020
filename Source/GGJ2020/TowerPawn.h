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
#include "Particles/ParticleSystemComponent.h"


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MeshHolding0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MeshHolding1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MeshHolding2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MeshHolding3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MeshHolding4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MeshHolding5;


	TArray<UStaticMeshComponent*> HoldingMeshes;

	//Is set when Hero gets reference to this!
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AHero* HeroRef;

	FRotator HeroExitRotation;

	void RotateAroundTower(float AxisValue);
	void MoveUpDown(float AxisValue);



	//------Up&Down Movement
	float sineInput{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float fUpperLimit;

	float DeltaTimeSample{ 0 };

	UPROPERTY(EditAnywhere, Category = Movement)
		float RotateMultiplier;

	UPROPERTY(EditAnywhere, Category = Movement)
		float UpDownMultiplier;



	//-----/

	//Jetpack thrust

	float WSValue{ 0 };
	float ADValue{ 0 };

	UFUNCTION(BlueprintImplementableEvent)
		void JetpackExhaust(float multiplier);

	UFUNCTION(BlueprintImplementableEvent)
		void TurnOnExhaust();

	UFUNCTION(BlueprintImplementableEvent)
		void TurnOffExhaust();


	//-/
	

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