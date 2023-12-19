// Fill out your copyright notice in the Description page of Project Settings.


#include "Rocket.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

#include "P38Filght.h"

// Sets default values
ARocket::ARocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComp->SetCollisionProfileName("OverlapAllDynamic");
	BoxComp->SetBoxExtent(FVector(25, 5, 5));	
	RootComponent = BoxComp;

	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>("RocketMesh");
	RocketMesh->SetupAttachment(BoxComp);
	RocketMesh->AddLocalRotation(FRotator(0, 270, 90));	//(Pitch=0.000000,Yaw=270.000000,Roll=90.000000)

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Rocket(TEXT("/Script/Engine.StaticMesh'/Game/Rocket/Meshes/SM_Rocket.SM_Rocket'"));
	if (Rocket.Succeeded())
	{
		RocketMesh->SetStaticMesh(Rocket.Object);
	}

	RocketMovement = CreateDefaultSubobject<UProjectileMovementComponent>("RocketMovement");

	RocketMovement->ProjectileGravityScale = 0.1f;
	RocketMovement->InitialSpeed = 1700.0f;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Explosion(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (Explosion.Succeeded())
	{
		ExplosionEffect = Explosion.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> BoomSound(TEXT("/Script/Engine.SoundWave'/Game/StarterContent/Audio/Explosion01.Explosion01'"));
	if (BoomSound.Succeeded())
	{
		ExplosionSound = BoomSound.Object;
	}
}

// Called when the game starts or when spawned
void ARocket::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(3.0f);

	OnActorBeginOverlap.AddDynamic(this, &ARocket::OnProcessOverlap);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ARocket::OnBeginOverlap);
}

// Called every frame
void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RocketMovement->Velocity = GetActorForwardVector() * RocketMovement->InitialSpeed;
	// 중력
	RocketMovement->Velocity.Z -= 980.0f * DeltaTime;
}

void ARocket::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());
	
	//AP38Filght* P38 = Cast<AP38Filght>(OtherActor);
	//// otheractor가 자기자신이 아니라면
	//if (OtherActor != this && OtherActor != P38)
	//{
	//	Explode();
	//}

}

void ARocket::Explode()
{
	FVector SpawnLocation = GetActorLocation();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorTransform());
	// 사운드 생성
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("boom"));
	Destroy();
}

void ARocket::OnProcessOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("actoractor"));
	AP38Filght* P38 = Cast<AP38Filght>(OtherActor);
	// otheractor가 자기자신이 아니라면
	if (OtherActor != this && OtherActor != P38)
	{
		Explode();
	}

}


