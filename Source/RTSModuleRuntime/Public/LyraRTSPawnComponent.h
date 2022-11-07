// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyraPawnComponent.h"
#include "LyraRTSPawnComponent.generated.h"

/**
 * Actor Component that handle RTS logic , handle selection and task queue
 */
UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class RTSMODULERUNTIME_API ULyraRTSPawnComponent : public ULyraPawnComponent
{
	GENERATED_BODY()

public:
	bool bIsSelected = false;

	UFUNCTION(BlueprintPure, Category = "RTS|Unit")
		bool GetIsSelected() const { return bIsSelected; }
};
