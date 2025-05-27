// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"

// Sets default values
AProjectileActor::AProjectileActor() {

	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay() {
	
	Super::BeginPlay();
}

void AProjectileActor::TongueAnim(FVector Dir, FVector Origin, float MaxDistance, float TSpeed) {
	
	bTongue = true;
	bRetracting = false;
	Direction = Dir.GetSafeNormal();
	TMaxDistance = MaxDistance;
	Speed = TSpeed;
	StartLocation = Origin;
}



// Called every frame
void AProjectileActor::Tick(float DeltaTime) {
	if (!bTongue) {
		Super::Tick(DeltaTime);
		FVector NewLocation = GetActorLocation() + Direction * Speed * DeltaTime;
		SetActorLocation(NewLocation);
		return;
	}

	FVector CurrentLocation = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Projectile at: %s"), *GetActorLocation().ToString());
	FVector Movement = Direction * Speed * DeltaTime;
	if (!bRetracting) {
		FVector NewLocation = CurrentLocation + Movement;
		SetActorLocation(NewLocation);

		if (FVector::Dist(StartLocation, NewLocation) >= TMaxDistance) {
			bRetracting = true;
		}
	}
	else {
		FVector NewLocation = CurrentLocation - Movement;
		SetActorLocation(NewLocation);

		if (FVector::Dist(NewLocation, StartLocation) <= 10.f) {
			Destroy();
		}

	}
}


