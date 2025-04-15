// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileSpawnerComponent.h"
#include "ProjectileActor.h"

// Sets default values for this component's properties
UProjectileSpawnerComponent::UProjectileSpawnerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

}

void UProjectileSpawnerComponent::FireRadialPattern() {

	if (ProjectileClass) {
	
		FVector Origin = GetOwner()->GetActorLocation();
		for (int i = 0; i < ProjectileCount; i++) {

			float AngleDeg = (SpreadAngle / ProjectileCount) * i;
			float AngleRad = FMath::DegreesToRadians(AngleDeg);
			FVector Direction = FVector(FMath::Cos(AngleRad), FMath::Sin(AngleRad), 0.0f).GetSafeNormal();
			FRotator SpawnRotation = Direction.Rotation();

			FActorSpawnParameters SpawnParams;
			AProjectileActor* Projectile = GetWorld()->SpawnActor<AProjectileActor>(ProjectileClass, Origin, SpawnRotation, SpawnParams);

			if (Projectile) {
				
				Projectile->Direction = Direction;
				//UE_LOG(LogTemp, Warning, TEXT("Projectile Direction %s"), *Direction.ToString());
				Projectile->SetLifeSpan(7.0f);
			}

		}
	}
}