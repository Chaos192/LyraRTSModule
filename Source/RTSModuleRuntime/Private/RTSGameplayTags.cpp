// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGameplayTags.h"

#include "Containers/Array.h"
#include "Engine/EngineTypes.h"
#include "GameplayTagsManager.h"
#include "Logging/LogCategory.h"
#include "Logging/LogMacros.h"
#include "LyraLogChannels.h"
#include "Trace/Detail/Channel.h"
#include "UObject/NameTypes.h"

FRTSGameplayTags FRTSGameplayTags::GameplayTags;

void FRTSGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

	GameplayTags.AddAllTags(Manager);

	// Notify manager that we are done adding native tags.
	Manager.DoneAddingNativeTags();
}


void FRTSGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{

	AddTag(InputTag_Camera_Move, "InputTag.Camera.RTS.Move", "RTS Camera Move input");
	AddTag(InputTag_Camera_RotateAxis, "InputTag.Camera.RTS.Rotate", "RTS Camera Rotate Axis input");
	AddTag(InputTag_Camera_TurnLeft, "InputTag.Camera.RTS.TurnLeft", "RTS Camera Turn Left input");
	AddTag(InputTag_Camera_TurnRight, "InputTag.Camera.RTS.TurnRight", "RTS Camera Turn Right input");
	AddTag(InputTag_Camera_Drag, "InputTag.Camera.RTS.Drag", "RTS Camera Drag input");
	AddTag(InputTag_Camera_Zoom, "InputTag.Camera.RTS.Zoom", "RTS Camera Zoom input");
	AddTag(InputTag_Camera_EdgeScroll, "InputTag.Camera.RTS.EdgeScroll", "RTS Camera EdgeScroll input");
	
	AddTag(GameplayEvent_Resign, "GameplayEvent.RTS.Resign", "Event that fires on rts play resign. This event only fires on the server.");
	AddTag(GameplayEvent_Win, "GameplayEvent.RTS.Win", "Event that fires once a rts player win");
	AddTag(GameplayEvent_Lose, "GameplayEvent.RTS.Lose", "Event that fires once a rts player lose");
	AddTag(GameplayEvent_RequestRematch, "GameplayEvent.RTS.RequestRematch", "Event to request a reset match");

	AddTag(Cheat_UnitGodMode, "Cheat.RTS.UnitGodMode", "GodMode for all controlled units cheat is active on the owner.");
	AddTag(Cheat_UnlimitedResources, "Cheat.RTS.UnlimitedResources", "UnlimitedHealth resources is active on the owner.");

}

void FRTSGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}

FGameplayTag FRTSGameplayTags::FindTagByString(FString TagString, bool bMatchPartialString)
{
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

	if (!Tag.IsValid() && bMatchPartialString)
	{
		FGameplayTagContainer AllTags;
		Manager.RequestAllGameplayTags(AllTags, true);

		for (const FGameplayTag TestTag : AllTags)
		{
			if (TestTag.ToString().Contains(TagString))
			{
				UE_LOG(LogLyra, Display, TEXT("Could not find exact match for tag [%s] but found partial match on tag [%s]."), *TagString, *TestTag.ToString());
				Tag = TestTag;
				break;
			}
		}
	}

	return Tag;
}
