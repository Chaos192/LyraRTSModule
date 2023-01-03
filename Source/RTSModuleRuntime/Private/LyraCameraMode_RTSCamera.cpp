// Fill out your copyright notice in the Description page of Project Settings.


#include "LyraCameraMode_RTSCamera.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Kismet/KismetMathLibrary.h"

ULyraCameraMode_RTSCamera::ULyraCameraMode_RTSCamera()
{
}

void ULyraCameraMode_RTSCamera::UpdateView(float DeltaTime)
{

	FVector PivotLocation = GetPivotLocation() + DefaultPivotRotation.Vector() * StartingHeight;
	FRotator PivotRotation = DefaultPivotRotation;

	PivotRotation.Pitch = FMath::ClampAngle(PivotRotation.Pitch, ViewPitchMin, ViewPitchMax);

	View.Location = PivotLocation;
	View.Rotation = PivotRotation;
	View.ControlRotation = GetPivotRotation();
	View.FieldOfView = FieldOfView;

	//ConfigureSpringArm();
}

void ULyraCameraMode_RTSCamera::DrawDebug(UCanvas* Canvas) const
{
}

void ULyraCameraMode_RTSCamera::FollowTarget(AActor* Target)
{
	CameraFollowTarget = Target;
}

void ULyraCameraMode_RTSCamera::UnFollowTarget()
{
	CameraFollowTarget = nullptr;
}

void ULyraCameraMode_RTSCamera::FollowTargetIfSet() const
{
}

void ULyraCameraMode_RTSCamera::SmoothTargetArmLengthToDesiredZoom() const
{
}

void ULyraCameraMode_RTSCamera::ConditionallyKeepCameraAtDesiredZoomAboveGround()
{
}

void ULyraCameraMode_RTSCamera::ConditionallyApplyCameraBounds() const
{
}

USceneComponent* ULyraCameraMode_RTSCamera::GetTargetRootComponent() const
{
	check(GetTargetActor())
	return Cast<USceneComponent>(GetTargetActor()->GetRootComponent());
}
