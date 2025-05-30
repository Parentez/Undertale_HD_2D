// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileActor.h"
#include "ProjectileSpawnerComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNDERTALE_HD_2D_API UProjectileSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UProjectileSpawnerComponent();

	void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(EditAnywhere, Category="Projectile")
	TSubclassOf<AProjectileActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	int ProjectileCount = 12;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float SpreadAngle = 360.0f;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void FireRadialPattern();

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void FallingRocks(float LineLength, int32 Count, float Duration);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void FrogTongue(FVector Dir, float LineLength, int x, int y);
};
