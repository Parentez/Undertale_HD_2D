// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "InputActionValue.h"
#include "Materials/MaterialParameterCollection.h"
#include "MyPlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class UNDERTALE_HD_2D_API AMyPlayerCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this charachter properties
	AMyPlayerCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to inputs
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; 

	// Called each frame to chek what animation needs to be used
	void UpdateAnimation();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialParameterCollection* MpcMask;
};
