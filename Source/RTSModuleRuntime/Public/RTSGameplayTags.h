// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Map.h"
#include "Containers/UnrealString.h"
#include "GameplayTagContainer.h"
#include "HAL/Platform.h"

class UGameplayTagsManager;

/**
 * FRTSGameplayTags
 *
 *	Singleton containing native gameplay tags.
 */
struct FRTSGameplayTags
{
public:

	static const FRTSGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();

	static FGameplayTag FindTagByString(FString TagString, bool bMatchPartialString = false);

public:

	FGameplayTag InputTag_Camera_Move;
	FGameplayTag InputTag_Camera_RotateAxis;
	FGameplayTag InputTag_Camera_TurnLeft;
	FGameplayTag InputTag_Camera_TurnRight;
	FGameplayTag InputTag_Camera_EdgeScroll;
	FGameplayTag InputTag_Camera_Drag;
	FGameplayTag InputTag_Camera_Zoom;

	FGameplayTag GameplayEvent_Resign;
	FGameplayTag GameplayEvent_Lose;
	FGameplayTag GameplayEvent_Win;
	FGameplayTag GameplayEvent_RequestRematch;

	FGameplayTag Cheat_UnitGodMode;
	FGameplayTag Cheat_UnlimitedResources;

protected:

	void AddAllTags(UGameplayTagsManager& Manager);
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

	static FRTSGameplayTags GameplayTags;
};
