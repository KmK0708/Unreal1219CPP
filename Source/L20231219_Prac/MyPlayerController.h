// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class L20231219_PRAC_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
AMyPlayerController();

	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		TObjectPtr<UInputMappingContext> InputContext;
};
