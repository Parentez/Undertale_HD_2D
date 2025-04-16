#include "MyPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h" 
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"

# define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT(text))
# define printFstring(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Magenta, FString::Printf(TEXT(text), (fstring)))
#include "EnhancedInputComponent.h"

AMyPlayerCharacter::AMyPlayerCharacter() {

	PrimaryActorTick.bCanEverTick = true;


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 1500.0f;
	SpringArm->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
}

void AMyPlayerCharacter::BeginPlay() {

	Super::BeginPlay();

	// Initialize the variables needed to check for battles
	StepsCounter = 0;
	StepsToBattle = FMath::RandRange(10, 50);
	LastPosition = GetActorLocation();
	EncountersNumber = 0;
	bInCombat = false;

	if (!FixedCamera) {
		TArray<AActor*> FoundCameras;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("FixedBattleCamera"), FoundCameras);
		if (FoundCameras.Num() > 0) {
			FixedCamera = Cast<ACameraActor>(FoundCameras[0]);
		}

	}

	// Automatically find HeartSpawm by tag
	if (!HeartSpawn) {
		TArray<AActor*> FoundSpawns;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("HeartSpawn"), FoundSpawns);
		if (FoundSpawns.Num() > 0) {
			HeartSpawn = FoundSpawns[0];
		}
	}

	if (!BattleManager) {
		TArray<AActor*> FoundManager;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("BP_BattleManager"), FoundManager);
		if (FoundManager.Num() > 0) {
			BattleManager = FoundManager[0];
		}
	}


	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem && DefaultMappingContext) {

			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		
	}
}

void AMyPlayerCharacter::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	// Creating the istance of the material parameters collection
	UMaterialParameterCollectionInstance* MPCInstance = GetWorld()->GetParameterCollectionInstance(MpcMask);
	FVector PlayerLocation = GetActorLocation();

	// Update the player position every frame for the mask material function
	MPCInstance->SetVectorParameterValue("PlayerLocation", PlayerLocation);

	// Add a Step and checks for battle
	if (!bInCombat) {
		float Distance = FVector::Dist(PlayerLocation, LastPosition);
		if (Distance > 100.0f) {
			StepsCounter++;
			printFstring("Steps Taken: %s", *FString::FromInt(StepsCounter));
			LastPosition = PlayerLocation;
			if (StepsCounter == StepsToBattle) {
				StartBattle();
			}
		}
	}
	
}

void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::Move);
	}
}

void AMyPlayerCharacter::Move(const FInputActionValue& Value) {
	
	if (!bInCombat) {  // stop the player movement if a battle starts 

		FVector2D MovementVector = Value.Get<FVector2D>();

		if (Controller) {
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			AddMovementInput(ForwardDirection, MovementVector.X);
			AddMovementInput(RightDirection, MovementVector.Y);
		}
	}

}

void AMyPlayerCharacter::StartBattle() {
	EncountersNumber += 10;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Battle Started"));
	StepsToBattle = FMath::RandRange(10 + EncountersNumber, 50 + FMath::FloorToInt(EncountersNumber * 1.25f));
	StepsCounter = 0;
	bInCombat = true;
	
	SwapPlayerControl();

	// Show widgtes
	HeartWidget = CreateWidget<UUserWidget>(GetWorld(), HeartWidgetClass);
	HeartWidget->AddToViewport();
}

void AMyPlayerCharacter::SwapPlayerControl() {
	
	if (!HeartPlayerClass || !HeartSpawn || !FixedCamera) {
		UE_LOG(LogTemp, Error, TEXT("Missing data in SwapPlayerControl. HeartPlayerClass: %s, HeartSpawn: %s, FixedCamera: %s"),
			*GetNameSafe(HeartPlayerClass), *GetNameSafe(HeartSpawn), *GetNameSafe(FixedCamera));
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	FVector SpawnLocation = HeartSpawn->GetActorLocation();
	FRotator SpawnRotation = HeartSpawn->GetActorRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = PlayerController;

	APaperZDCharacter* HeartPlayer = GetWorld()->SpawnActor<APaperZDCharacter>(HeartPlayerClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (HeartPlayer && FixedCamera) {
		
		PlayerController->Possess(HeartPlayer);
		PlayerController->SetViewTarget(FixedCamera);

	}

	FOutputDeviceNull ar;
	const FString command = FString::Printf(TEXT("HandleState"));
	if (BattleManager) {
		BattleManager->CallFunctionByNameWithArguments(*command, ar, NULL, true);
		
	}
}

