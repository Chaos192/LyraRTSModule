// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Camera/LyraCameraMode.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneComponent.h"
#include "LyraCameraMode_RTSCamera.generated.h"

class USceneComponent;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class RTSMODULERUNTIME_API ULyraCameraMode_RTSCamera : public ULyraCameraMode
{
	GENERATED_BODY()

public:

	ULyraCameraMode_RTSCamera();

protected:

	virtual void UpdateView(float DeltaTime) override;
	virtual void DrawDebug(UCanvas* Canvas) const override;

public:
	UFUNCTION(BlueprintCallable, Category = "RTSCamera")
		void FollowTarget(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "RTSCamera")
		void UnFollowTarget();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTSCamera - Zoom Settings")
		float MinimumZoomLength = 500;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTSCamera - Zoom Settings")
		float MaximumZoomLength = 5000;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTSCamera - Zoom Settings")
		float ZoomCatchupSpeed = 4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTSCamera - Zoom Settings")
		float ZoomSpeed = -200;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTSCamera")
		FRotator DefaultPivotRotation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTSCamera")
		float StartingHeight = 10000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTSCamera")
		float MoveSpeed = 50;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTSCamera")
		float RotateSpeed = 45;

	/**
 * Controls how fast the drag will move the camera.
 * Higher values will make the camera move more slowly.
 * The drag speed is calculated as follows:
 *	DragSpeed = MousePositionDelta / (ViewportExtents * DragExtent)
 * If the drag extent is small, the drag speed will hit the "max speed" of `this->MoveSpeed` more quickly.
 */
	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		Category = "RTSCamera",
		meta = (ClampMin = "0.0", ClampMax = "1.0")
	)
		float DragExtent = 0.6f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTSCamera")
		bool EnableCameraLag = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTSCamera")
		bool EnableCameraRotationLag = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTSCamera - Dynamic Camera Height Settings")
		bool EnableDynamicCameraHeight = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RTSCamera - Dynamic Camera Height Settings")
		TEnumAsByte<ECollisionChannel> CollisionChannel;
	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		Category = "RTSCamera - Dynamic Camera Height Settings",
		meta = (EditCondition = "EnableDynamicCameraHeight")
	)
		float FindGroundTraceLength = 100000;


private:

	void FollowTargetIfSet() const;
	void SmoothTargetArmLengthToDesiredZoom() const;
	void ConditionallyKeepCameraAtDesiredZoomAboveGround();
	void ConditionallyApplyCameraBounds() const;

	USceneComponent* GetTargetRootComponent() const;

	UPROPERTY()
		FName CameraBlockingVolumeTag;
	UPROPERTY()
		AActor* CameraFollowTarget;
	UPROPERTY()
		float DeltaSeconds;
	UPROPERTY()
		bool IsCameraOutOfBoundsErrorAlreadyDisplayed;
	UPROPERTY()
		FVector2D DragStartLocation;
};
