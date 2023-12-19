// Fill out your copyright notice in the Description page of Project Settings.


#include "P38Filght.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputactionValue.h"
#include "Rocket.h"

// Sets default values
AP38Filght::AP38Filght()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(45, 45, 5));
	RootComponent = BoxComp;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(BoxComp);

	LPropeller = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LPropeller"));
	LPropeller->SetupAttachment(Body);

	RPropeller = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RPropeller"));
	RPropeller->SetupAttachment(Body);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(BoxComp);
	Arrow->AddLocalOffset(FVector(80, 0, 0));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BoxComp);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->AddLocalOffset(FVector(0, 0, 90));

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMesh(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));
	if (BodyMesh.Succeeded())
	{
		Body->SetStaticMesh(BodyMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (Propeller.Succeeded())
	{
		LPropeller->SetStaticMesh(Propeller.Object);
		RPropeller->SetStaticMesh(Propeller.Object);
	}
	RPropeller->AddLocalOffset(FVector(37, 21, 0));
	LPropeller->AddLocalOffset(FVector(37, -21, 0));

	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 6.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 6.0f;
}

// Called when the game starts or when spawned
void AP38Filght::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP38Filght::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), 0.2f);

	RPropeller->AddLocalRotation(FRotator(0, 0, 1000 * DeltaTime));
	LPropeller->AddLocalRotation(FRotator(0, 0, 1000 * DeltaTime));
}

// Called to bind functionality to input
void AP38Filght::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//입력받기(구버전)
//	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AP38Filght::Fire);
//	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AP38Filght::Pitch);
//	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AP38Filght::Roll);

	//입력받기(신버전)
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIC && FireAction && Pitch_RollAction)
	{
		EIC->BindAction(FireAction, ETriggerEvent::Triggered, this, &AP38Filght::Fire);
		EIC->BindAction(Pitch_RollAction, ETriggerEvent::Triggered, this, &AP38Filght::Pitch_Roll);
	}
}

void AP38Filght::Fire(const FInputActionValue& Value)
{
	if (RocketTemplate)
	{
		//로켓스폰
		FVector Location = Arrow->GetComponentLocation();
		FRotator Rotation = Arrow->GetComponentRotation();
		ARocket* Rocket = GetWorld()->SpawnActor<ARocket>(RocketTemplate, Location, Rotation);
	}
}

void AP38Filght::Pitch_Roll(const FInputActionValue& Value)
{
	// delta time을 곱해줘야 프레임에 따라 속도가 달라지지 않는다.
	FVector2D RotationValue = Value.Get<FVector2D>();
	// 60프레임으로 고정
	if (!RotationValue.IsZero())
	{
		RotationValue = RotationValue * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f;

		AddActorLocalRotation(FRotator(RotationValue.Y, 0, RotationValue.X));

	}
}

//void AP38Filght::Fire()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Fire"));
//	//로켓스폰
//	FVector Location = Arrow->GetComponentLocation();
//	FRotator Rotation = Arrow->GetComponentRotation();
//	ARocket* Rocket = GetWorld()->SpawnActor<ARocket>(Location, Rotation);
//	
//}
//
//void AP38Filght::Pitch(float Value)
//{
//	if (Value != 0)
//	{
//		AddActorLocalRotation(FRotator(Value * 50 * GetWorld()->DeltaTimeSeconds, 0, 0));
//	}
//}
//
//void AP38Filght::Roll(float Value)
//{
//	if (Value != 0)
//	{
//		AddActorLocalRotation(FRotator(0, 0, Value * 50 * GetWorld()->DeltaTimeSeconds));
//	}
//}

