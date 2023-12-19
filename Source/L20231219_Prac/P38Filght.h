// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "InputActionValue.h"

#include "P38Filght.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class USceneComponent;
class UArrowComponent;
class UFloatingPawnMovement;
class UInputMappingContext;
class UInputAction;
class ARocket;

UCLASS()
class L20231219_PRAC_API AP38Filght : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AP38Filght();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 비행체의 구성요소들
public:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* LPropeller;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* RPropeller;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* Arrow;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Movement")
	UFloatingPawnMovement* Movement;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")
	TSubclassOf<ARocket> RocketTemplate;

public:
// 향상된 입력
	// 플레이어 인풋 맵핑컨텍스트
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	class UInputMappingContext* IMC_Main;
	// 인풋 액션
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<class UInputAction> Pitch_RollAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<class UInputAction> FireAction;

// 비행체의 움직임
	void Fire(const FInputActionValue& Value);

	void Pitch_Roll(const FInputActionValue& Value);

};
