// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileSpawnerComponent.h"
#include "ProjectileActor.h"

// Sets default values for this component's properties
UProjectileSpawnerComponent::UProjectileSpawnerComponent() {

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
				Projectile->SetLifeSpan(5.0f);
			}

		}
	}
}

void UProjectileSpawnerComponent::FallingRocks(float LineLength, int32 Count, float Duration) {
	if (!ProjectileClass || Count <= 0 || Duration <= 0.f) return;

	FVector Origin = GetOwner()->GetActorLocation();
	UWorld* World = GetWorld();

	for (int32 i = 0; i < Count; ++i) {
		// Random delay between 0 and Duration
		float Delay = FMath::FRandRange(0.f, Duration);

		// Use a timer to delay each spawn
		FTimerHandle TimerHandle;
		World->GetTimerManager().SetTimer(TimerHandle, [this, Origin, LineLength]() {
			// Calculate a random point along the horizontal line
			float Offset = FMath::FRandRange(-LineLength / 2.0f, LineLength / 2.0f);
			FVector SpawnLocation = Origin + FVector(0.f, Offset, 0.f); // 2D X axis line
			FVector Direction = FVector(-1.f, 0.f, 0.f); // Downward in Y

			FRotator SpawnRotation = Direction.Rotation();
			FActorSpawnParameters SpawnParams;

			AProjectileActor* Projectile = GetWorld()->SpawnActor<AProjectileActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
			if (Projectile) {
				Projectile->Direction = Direction;
				Projectile->SetLifeSpan(5.0f);
			}
		}, Delay, false);
	}
}