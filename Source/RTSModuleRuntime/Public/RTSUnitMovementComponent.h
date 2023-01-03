// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyraCharacterMovementComponent.h"
#include "RTSUnitMovementComponent.generated.h"

/**
 * 
 */
UCLASS(Config = Game)
class RTSMODULERUNTIME_API URTSUnitMovementComponent : public ULyraCharacterMovementComponent
{
	GENERATED_BODY()

public:
	URTSUnitMovementComponent(const FObjectInitializer& ObjectInitializer);
};
