// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "Teams/LyraTeamAgentInterface.h"
#include "AbilitySystemInterface.h"
#include "GameplayCueInterface.h"
#include "Character/LyraPawnExtensionComponent.h"
#include "LyraRTSPawnComponent.generated.h"


class ALyraPlayerController;
class ALyraPlayerState;
class ULyraAbilitySystemComponent;
class UAbilitySystemComponent;
class ULyraPawnExtensionComponent;
class ULyraCameraComponent;

/**
 * Actor Component that handle RTS logic , handle selection and task queue
 */
UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class RTSMODULERUNTIME_API ULyraRTSPawnComponent : public ULyraPawnExtensionComponent
{
	GENERATED_BODY()

public:

	bool bIsSelected = false;

	UFUNCTION(BlueprintPure, Category = "RTS|Unit")
		bool GetIsSelected() const { return bIsSelected; }

};
