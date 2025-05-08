#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "InputActionValue.h"
#include "Misc/OutputDeviceNull.h"
#include "Materials/MaterialParameterCollection.h"
#include "MyPlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class ACameraActor;

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

	bool bInCombat;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Exit Combat")
	void ExitCombat();

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void StartBattle();

	UFUNCTION(BlueprintCallable, Category = "Swap Player")
	void SwapPlayerControl();
	
	UFUNCTION(BlueprintCallable, Category = "Combat Transition")
	void SceneTransition();

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat Transition")
	void ZoomTransition();

	UFUNCTION()
	void ShowFadeWidget();
	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fixed Heart Camera")
	ACameraActor* FixedCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn heart point")
	AActor* HeartSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Player Swap")
	TSubclassOf<APaperZDCharacter> HeartPlayerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
	AActor* BattleManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Transition")
	TSubclassOf<UUserWidget> FadeTransitionClass;
	UUserWidget* FadeWidget;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	UInputAction* ExitCombatt;

	UPROPERTY()
	APaperZDCharacter* CurrentHeart;

private:
	int StepsCounter;
	int StepsToBattle;
	int EncountersNumber;
	FVector LastPosition;
	FTimerHandle TransitionTimer;
	FTimerHandle FadeTimer;
};
