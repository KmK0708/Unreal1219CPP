// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "MyPlayerController.h"
#include "P38Filght.h"

AMyGameModeBase::AMyGameModeBase()
{
	UE_LOG(LogTemp, Warning, TEXT("Ahhhhp"));

	// 디버그 로그
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, TEXT("LPOP"));
	}

	DefaultPawnClass = AP38Filght::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
