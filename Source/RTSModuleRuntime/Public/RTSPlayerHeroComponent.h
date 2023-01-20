// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyraHeroComponent.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "Containers/Array.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "GameplayAbilitySpec.h"
#include "Input/LyraMappableConfigPair.h"
#include "Templates/SubclassOf.h"
#include "UObject/NameTypes.h"
#include "UObject/UObjectGlobals.h"
#include "Input/LyraInputComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "RTSPlayerHeroComponent.generated.h"

class UGameFrameworkComponentManager;
class UInputComponent;
class ULyraCameraMode;
class ULyraInputConfig;
class UObject;
struct FActorInitStateChangedParams;
struct FFrame;
struct FGameplayTag;
struct FInputActionValue;

struct FCameraMovementCommand
{
    FVector Direction;
	float Rotation;
	float Scale;
	FGameplayTagContainer CameraTag;
};

/**
 * 
 */
UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class RTSMODULERUNTIME_API URTSPlayerHeroComponent : public ULyraHeroComponent
{
	GENERATED_BODY()
public:

	URTSPlayerHeroComponent(const FObjectInitializer& ObjectInitializer);

	/** Returns the hero component if one exists on the specified actor. */
	UFUNCTION(BlueprintPure, Category = "RTS")
	static URTSPlayerHeroComponent* FindRTSPlayerComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<URTSPlayerHeroComponent>() : nullptr); }


	UFUNCTION(BlueprintCallable, Category = "RTSCamera")
		void FollowTarget(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "RTSCamera")
		void UnFollowTarget();

	UFUNCTION(BlueprintCallable, Category = "Lyra")
		ALyraCharacter* GetLyraCharacter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTSCamera - Edge Scroll Settings")
		bool EnableEdgeScrolling=true;
	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		Category = "RTSCamera - Edge Scroll Settings",
		meta = (EditCondition = "EnableEdgeScrolling")
	)
		float EdgeScrollSpeed = 50;
	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		Category = "RTSCamera - Edge Scroll Settings",
		meta = (EditCondition = "EnableEdgeScrolling")
	)
		float DistanceFromEdgeThreshold = 0.05f;

protected:

	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void InitializePlayerInput(UInputComponent* PlayerInputComponent) override;

	void Input_MoveCamera(const FInputActionValue& InputActionValue);
	void Input_DragCamera(const FInputActionValue& InputActionValue);
	void Input_ZoomCamera(const FInputActionValue& InputActionValue);
	void Input_EdgeScrollCamera(const FInputActionValue& InputActionValue);
	void Input_RotateCameraLeft(const FInputActionValue& InputActionValue);
	void Input_RotateCameraRight(const FInputActionValue& InputActionValue);
private:
	void QueueCameraMovementCommand(const FVector Direction, const double Scale, FGameplayTagContainer CameraMovementTags);
	void QueueCameraRotationCommand(const float Rotation, FGameplayTagContainer CameraMovementTags);
	void ApplyMoveCameraCommands();
	void ConditionallyEnableEdgeScrolling() const;
	void ConditionallyPerformEdgeScrolling();
	void EdgeScrollLeft();
	void EdgeScrollRight();
	void EdgeScrollUp();
	void EdgeScrollDown();

	void BindInputTags( ULyraInputComponent* PlayerInputComponent, const ULyraInputConfig* InputConfig);

	TQueue<FCameraMovementCommand> CameraMovementCommandQueue;

	UPROPERTY()
		float DeltaSeconds;
	UPROPERTY()
		bool IsDragging=false;
	UPROPERTY()
		FVector2D DragStartLocation;
	UPROPERTY()
		float DragExtent=0.01f;
};

