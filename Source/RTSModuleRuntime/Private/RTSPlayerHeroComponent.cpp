// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerHeroComponent.h"
#include "LyraLogChannels.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/LyraPlayerController.h"
#include "Player/LyraPlayerState.h"
#include "Player/LyraLocalPlayer.h"
#include "Character/LyraPawnExtensionComponent.h"
#include "Character/LyraPawnData.h"
#include "Character/LyraCharacter.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "Input/LyraInputConfig.h"
#include "Camera/LyraCameraComponent.h"
#include "LyraGameplayTags.h"
#include "RTSGameplayTags.h"
#include "Engine/LocalPlayer.h"
#include "Components/GameFrameworkComponentManager.h"
#include "Settings/LyraSettingsLocal.h"
#include "System/LyraAssetManager.h"
#include "PlayerMappableInputConfig.h"
#include "Input/LyraMappableConfigPair.h"
#include "Camera/LyraCameraMode.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RTSPlayerHeroComponent)



URTSPlayerHeroComponent::URTSPlayerHeroComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityCameraMode = nullptr;
	bReadyToBindInputs = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	bAutoActivate = false;
}

void URTSPlayerHeroComponent::FollowTarget(AActor* Target)
{
}

void URTSPlayerHeroComponent::UnFollowTarget()
{
}

ALyraCharacter* URTSPlayerHeroComponent::GetLyraCharacter()
{
	return GetPawnChecked<ALyraCharacter>();
}

void URTSPlayerHeroComponent::OnRegister()
{
	Super::OnRegister();
}

void URTSPlayerHeroComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void URTSPlayerHeroComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ConditionallyPerformEdgeScrolling();
	ApplyMoveCameraCommands();
	DeltaSeconds = DeltaTime;
}


void URTSPlayerHeroComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void URTSPlayerHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	const ULyraLocalPlayer* LP = Cast<ULyraLocalPlayer>(PC->GetLocalPlayer());
	check(LP);

	//ConditionallyEnableEdgeScrolling();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();

	if (const ULyraPawnExtensionComponent* PawnExtComp = ULyraPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const ULyraPawnData* PawnData = PawnExtComp->GetPawnData<ULyraPawnData>())
		{
			if (const ULyraInputConfig* InputConfig = PawnData->InputConfig)
			{
			/*	const FRTSGameplayTags& GameplayTags = FRTSGameplayTags::Get();*/

				// Register any default input configs with the settings so that they will be applied to the player during AddInputMappings
				for (const FMappableConfigPair& Pair : DefaultInputConfigs)
				{
					{
						FModifyContextOptions Options = {};
						Options.bIgnoreAllPressedKeysUntilRelease = false;
						// Actually add the config to the local player							
						Subsystem->AddPlayerMappableConfig(Pair.Config.LoadSynchronous(), Options);
					}
				}

				// Need to change expose LyInputConfig and LyraInputComponent
				ULyraInputComponent* LyraIC = CastChecked<ULyraInputComponent>(PlayerInputComponent);
				LyraIC->AddInputMappings(InputConfig, Subsystem);

				TArray<uint32> BindHandles;
				LyraIC->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);

				BindInputTags(LyraIC, InputConfig);

			}
		}
	}

	if (ensure(!bReadyToBindInputs))
	{
		bReadyToBindInputs = true;
	}

	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(const_cast<APlayerController*>(PC), NAME_BindInputsNow);
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(const_cast<APawn*>(Pawn), NAME_BindInputsNow);
}

void URTSPlayerHeroComponent::Input_MoveCamera(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;

	// If the player has attempted to move again then cancel auto running
	if (ALyraPlayerController* LyraController = Cast<ALyraPlayerController>(Controller))
	{
		LyraController->SetIsAutoRunning(false);
	}

	if (Controller)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			//Pawn->AddMovementInput(MovementDirection, Value.X);
			QueueCameraMovementCommand(MovementDirection, Value.X, TAG_Camera_Move);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			//Pawn->AddMovementInput(MovementDirection, Value.Y);
			QueueCameraMovementCommand(MovementDirection, Value.Y, TAG_Camera_Move);
		}
	}
}

void URTSPlayerHeroComponent::Input_DragCamera(const FInputActionValue& InputActionValue)
{
	if (!IsDragging && InputActionValue.Get<bool>())
	{
		IsDragging = true;
		DragStartLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	}

	else if (IsDragging && InputActionValue.Get<bool>())
	{
		APawn* Pawn = GetPawn<APawn>();
		AController* Controller = Pawn ? Pawn->GetController() : nullptr;

		// If the player has attempted to move again then cancel auto running
		if (ALyraPlayerController* LyraController = Cast<ALyraPlayerController>(Controller))
		{
			LyraController->SetIsAutoRunning(false);
		}

		const auto MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		auto DragExtents = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize();
		DragExtents *= DragExtent;

		auto Delta = MousePosition - DragStartLocation;
		Delta.X = FMath::Clamp(Delta.X, -DragExtents.X, DragExtents.X) / DragExtents.X;
		Delta.Y = FMath::Clamp(Delta.Y, -DragExtents.Y, DragExtents.Y) / DragExtents.Y;

		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		QueueCameraMovementCommand(
			MovementRotation.RotateVector(FVector::RightVector),
			Delta.X, TAG_Camera_Drag);

		QueueCameraMovementCommand(
			MovementRotation.RotateVector(FVector::ForwardVector),
			Delta.Y * -1, TAG_Camera_Drag);

	}

	else if (IsDragging && !InputActionValue.Get<bool>())
	{
		IsDragging = false;
	}
}

void URTSPlayerHeroComponent::Input_EdgeScrollCamera(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogRTS, Display, TEXT("RTS EdgeScroll Camera. [%s]"), *InputActionValue.ToString());

	ConditionallyPerformEdgeScrolling();
}

void URTSPlayerHeroComponent::Input_RotateCameraLeft(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	Pawn->AddControllerYawInput(-90.0f);
	Pawn->SetActorRelativeRotation(
		FRotator::MakeFromEuler(
			FVector(
				0.0f,
				0.0,
				-90.0f
			)
		)
	);
	UE_LOG(LogRTS, Display, TEXT("RTS Rotate Camera Left."));
}

void URTSPlayerHeroComponent::Input_RotateCameraRight(const FInputActionValue& InputActionValue)
{

	APawn* Pawn = GetPawn<APawn>();
	Pawn->AddControllerYawInput(90.0f);
	Pawn->SetActorRelativeRotation(
		FRotator::MakeFromEuler(
			FVector(
				0,
				0,
				90
			)
		)
	);
	UE_LOG(LogRTS, Display, TEXT("RTS Rotate Camera Right."));
}

void URTSPlayerHeroComponent::QueueCameraMovementCommand(const FVector Direction, const float Scale, FGameplayTag CameraMovementTag)
{
	FCameraMovementCommand MovementCommand;
	MovementCommand.Direction = Direction;
	MovementCommand.Scale = Scale;
	MovementCommand.CameraTag = CameraMovementTag;
	CameraMovementCommandQueue.Enqueue(MovementCommand);
}

void URTSPlayerHeroComponent::ApplyMoveCameraCommands()
{
	APawn* Pawn = GetPawn<APawn>();
	while(!CameraMovementCommandQueue.IsEmpty())
	{
		FCameraMovementCommand MovementCommand;
		CameraMovementCommandQueue.Dequeue(MovementCommand);
		Pawn->AddMovementInput(
			MovementCommand.Direction, MovementCommand.Scale
		);
		UE_LOG(LogRTS, Display, TEXT("RTS Camera Movement. [%s]"), *MovementCommand.CameraTag.ToString());
	}
}

void URTSPlayerHeroComponent::ConditionallyEnableEdgeScrolling() const
{
	if (EnableEdgeScrolling)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		InputMode.SetHideCursorDuringCapture(false);
		APlayerController* PC = GetController<APlayerController>();
		check(PC);
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
}

void URTSPlayerHeroComponent::ConditionallyPerformEdgeScrolling() const
{
	if (EnableEdgeScrolling && !IsDragging)
	{
		
		EdgeScrollLeft();
		EdgeScrollRight();
		EdgeScrollUp();
		EdgeScrollDown();
	}
}

void URTSPlayerHeroComponent::EdgeScrollLeft() const
{
	APawn* Pawn = GetPawn<APawn>();
	//UE_LOG(LogRTS, Display, TEXT("RTS EdgeScroll Camera Left."));
	const auto MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	const auto ViewportSize = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize();
	const auto NormalizedMousePosition = 1 - UKismetMathLibrary::NormalizeToRange(
		MousePosition.X,
		0.0f,
		ViewportSize.X * 0.05f
	);

	const auto Movement = UKismetMathLibrary::FClamp(NormalizedMousePosition, 0.0, 1.0);
	const auto Direction = GetOwner()->GetActorRightVector();
	if (Movement > 0.0f) {
		UE_LOG(LogRTS, Display, TEXT("RTS EdgeScroll Camera Left. [%d]"), Movement);
		Pawn->AddMovementInput(
			-1 * Direction, Movement * EdgeScrollSpeed
		);
	}
}

void URTSPlayerHeroComponent::EdgeScrollRight() const
{
	APawn* Pawn = GetPawn<APawn>();
	const auto MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	const auto ViewportSize = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize();
	const auto NormalizedMousePosition = UKismetMathLibrary::NormalizeToRange(
		MousePosition.X,
		ViewportSize.X * 0.95f,
		ViewportSize.X
	);

	const auto Movement = UKismetMathLibrary::FClamp(NormalizedMousePosition, 0.0, 1.0);
	const auto Direction = GetOwner()->GetActorRightVector();
	
	if (Movement > 0.0f) {
		UE_LOG(LogRTS, Display, TEXT("RTS EdgeScroll Camera Right. [%d]"), Movement);
		Pawn->AddMovementInput(
			Direction, Movement * EdgeScrollSpeed
		);
	}
}

void URTSPlayerHeroComponent::EdgeScrollUp() const
{
	APawn* Pawn = GetPawn<APawn>();
	const auto MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	const auto ViewportSize = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize();
	const auto NormalizedMousePosition = UKismetMathLibrary::NormalizeToRange(
		MousePosition.Y,
		0.0f,
		ViewportSize.Y * 0.05f
	);

	const auto Movement = 1 - UKismetMathLibrary::FClamp(NormalizedMousePosition, 0.0, 1.0);
	const auto Direction = GetOwner()->GetActorForwardVector();

	if (Movement > 0.0f) {
		UE_LOG(LogRTS, Display, TEXT("RTS EdgeScroll Camera Right. [%d]"), Movement);
		Pawn->AddMovementInput(
			Direction, Movement * EdgeScrollSpeed
		);
	}
}

void URTSPlayerHeroComponent::EdgeScrollDown() const
{
	APawn* Pawn = GetPawn<APawn>();
	const auto MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	const auto ViewportSize = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize();
	const auto NormalizedMousePosition = UKismetMathLibrary::NormalizeToRange(
		MousePosition.Y,
		ViewportSize.Y * 0.95f,
		ViewportSize.Y
	);

	const auto Movement = UKismetMathLibrary::FClamp(NormalizedMousePosition, 0.0, 1.0);
	const auto Direction = GetOwner()->GetActorForwardVector();

	if (Movement > 0.0f) {
		UE_LOG(LogRTS, Display, TEXT("RTS EdgeScroll Camera Right. [%d]"), Movement);
		Pawn->AddMovementInput(
			-1 * Direction, Movement * EdgeScrollSpeed
		);
	};
}

void URTSPlayerHeroComponent::BindInputTags(ULyraInputComponent* PlayerInputComponent, const ULyraInputConfig* InputConfig)
{
	PlayerInputComponent->BindNativeAction(InputConfig, InputTag_Camera_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_MoveCamera, /*bLogIfNotFound=*/ false);
	PlayerInputComponent->BindNativeAction(InputConfig, InputTag_Camera_TurnLeft, ETriggerEvent::Triggered, this, &ThisClass::Input_RotateCameraLeft, /*bLogIfNotFound=*/ false);
	PlayerInputComponent->BindNativeAction(InputConfig, InputTag_Camera_TurnRight, ETriggerEvent::Triggered, this, &ThisClass::Input_RotateCameraRight, /*bLogIfNotFound=*/ false);
	//PlayerInputComponent->BindNativeAction(InputConfig, InputTag_Camera_EdgeScroll, ETriggerEvent::Triggered, this, &ThisClass::Input_EdgeScrollCamera, /*bLogIfNotFound=*/ false);
	PlayerInputComponent->BindNativeAction(InputConfig, InputTag_Camera_Drag, ETriggerEvent::Triggered, this, &ThisClass::Input_DragCamera, /*bLogIfNotFound=*/ false);
}
