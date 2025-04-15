// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

UCLASS()
class UNDERTALE_HD_2D_API AProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Speed = 750.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FVector Direction;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
