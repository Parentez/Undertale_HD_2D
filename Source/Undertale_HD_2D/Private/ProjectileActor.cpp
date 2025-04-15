// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"

// Sets default values
AProjectileActor::AProjectileActor() {

	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay() {
	
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Projectile spawned!"));
	
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation() + Direction * Speed * DeltaTime;

	SetActorLocation(NewLocation);
}

