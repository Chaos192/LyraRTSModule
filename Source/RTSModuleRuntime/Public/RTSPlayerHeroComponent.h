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
		float DistanceFromEdgeThreshold = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
		FGameplayTag InputTag_Camera_Move;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag_Camera_RotateAxis;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag_Camera_TurnLeft;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag_Camera_TurnRight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag_Camera_EdgeScroll;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag_Camera_Drag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag_Camera_Zoom;
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

private:
	void ConditionallyEnableEdgeScrolling() const;
	void ConditionallyPerformEdgeScrolling() const;
	void EdgeScrollLeft() const;
	void EdgeScrollRight() const;
	void EdgeScrollUp() const;
	void EdgeScrollDown() const;

	void BindInputTags( ULyraInputComponent* PlayerInputComponent, const ULyraInputConfig* InputConfig);

	UPROPERTY()
		float DeltaSeconds;
	UPROPERTY()
		bool IsDragging;
};
