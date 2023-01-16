// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "NativeGameplayTags.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Camera_Move);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Camera_Drag);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Camera_EdgeScroll);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Camera_Turn);

struct FRTSGameplayTags : public FGameplayTagNativeAdder
{
//	//Tag used for Fire Damage
//	FGameplayTag Damage_Fire;
//
	//Static accessor for accessing the tags. Access tags using:
	//FRTSGameplayTags::Get().Damage_Fire for example.
	FORCEINLINE static const FRTSGameplayTags& Get() { return RTSGameplayTags; }

//protected:
//	//Called to register and assign the native tags
//	virtual void AddTags() override
//	{
//		UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
//
//		Damage_Fire = Manager.AddNativeGameplayTag(TEXT("Status.Damage.Fire"));
//	}
//
//
private:
	//Private static object for the global tags. Use the Get() function to access externally.
	static FRTSGameplayTags RTSGameplayTags;
};