// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rocket.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystem;
class USoundBase;
class UProjectileMovementComponent;

UCLASS()
class L20231219_PRAC_API ARocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = "Collision")
		UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		UStaticMeshComponent* RocketMesh;

	UPROPERTY(EditAnywhere, Category = "Rocket")
		float Speed;

	UPROPERTY(EditAnywhere, Category = "Rocket")
		float LifeTime = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Rocket")
		float Damage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		UParticleSystem* ExplosionEffect;

	UPROPERTY(EditAnywhere, Category = "Movement")
		UProjectileMovementComponent* RocketMovement;


	// 박스오버랩시작
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void Explode();

	UFUNCTION()
	void OnProcessOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
