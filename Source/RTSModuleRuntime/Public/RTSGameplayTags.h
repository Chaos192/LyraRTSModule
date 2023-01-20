// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

struct RTSMODULERUNTIME_API FRTSGameplayTags : public FGameplayTagNativeAdder
{
public:
	//Tag used for Fire Damage
	FGameplayTag Damage_Fire;

	FGameplayTag Input_CameraDrag;
	FGameplayTag Input_CameraMove;
	FGameplayTag Input_CameraEdgeScroll;
	FGameplayTag Input_CameraRotateAxis;
	FGameplayTag Input_CameraTurnLeft;
	FGameplayTag Input_CameraTurnRight;
	FGameplayTag Input_CameraZoom;
public:
//
	//Static accessor for accessing the tags. Access tags using:
	//FRTSGameplayTags::Get().Damage_Fire for example.
	FORCEINLINE static const FRTSGameplayTags& Get() { return RTSGameplayTags; }

protected:
//	//Called to register and assign the native tags
	virtual void AddTags() override
	{
		UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

		Damage_Fire = Manager.AddNativeGameplayTag(TEXT("Status.Damage.Fire"));
		
		Input_CameraDrag = Manager.AddNativeGameplayTag(TEXT("InputTag.Camera.Drag"));
		Input_CameraEdgeScroll = Manager.AddNativeGameplayTag(TEXT("InputTag.Camera.EdgeScroll"));
		Input_CameraMove = Manager.AddNativeGameplayTag(TEXT("InputTag.Camera.Move"));
		Input_CameraRotateAxis = Manager.AddNativeGameplayTag(TEXT("InputTag.Camera.RotateAxis"));
		Input_CameraTurnLeft = Manager.AddNativeGameplayTag(TEXT("InputTag.Camera.TurnLeft"));
		Input_CameraTurnRight = Manager.AddNativeGameplayTag(TEXT("InputTag.Camera.TurnRight"));
		Input_CameraZoom = Manager.AddNativeGameplayTag(TEXT("InputTag.Camera.Zoom"));
	}
//
//
private:
	//Private static object for the global tags. Use the Get() function to access externally.
	static FRTSGameplayTags RTSGameplayTags;
};