// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileSpawnerComponent.h"
#include "Kismet/GameplayStatics.h"
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
	float LastOffset = LineLength;

	for (int32 i = 0; i < Count; ++i) {
		float Delay = FMath::FRandRange(0.f, Duration);

		FTimerHandle TimerHandle;
		World->GetTimerManager().SetTimer(TimerHandle, [this, Origin, LineLength, &LastOffset]() {
			
			
			float Offset = FMath::FRandRange(-LineLength / 2.0f, LineLength / 2.0f);
			if (LastOffset <= Offset + 20.f && LastOffset >= Offset - 20.f) {
				Offset -= LastOffset;
			}
			LastOffset = Offset;
			FVector SpawnLocation = Origin + FVector(0.f, Offset, 0.f); 
			FVector Direction = FVector(-1.f, 0.f, 0.f);

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

void UProjectileSpawnerComponent::FrogTongue(FVector Dir, float LineLength, int x, int y) {

	if (ProjectileClass) {
		FVector Origin = GetOwner()->GetActorLocation();
		FVector Direction = Dir.GetSafeNormal();
		FRotator SpawnRotation = Direction.Rotation();

		float Offset = FMath::FRandRange(-LineLength / 2.0f, LineLength / 2.0f);
		FVector SpawnLocation = Origin + FVector(x, y, 0.f) * Offset;
		UE_LOG(LogTemp, Warning, TEXT("SpawnLocation: %s"), *SpawnLocation.ToString());
		FActorSpawnParameters SpawnParams;
		AProjectileActor* Projectile = GetWorld()->SpawnActor<AProjectileActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (Projectile) {
			Projectile->TongueAnim(Direction, SpawnLocation, 2800.f, 1200.f); // Max distance, speed
		}

	}

}