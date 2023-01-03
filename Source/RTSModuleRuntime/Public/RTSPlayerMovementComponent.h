// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyraCharacterMovementComponent.h"
#include "RTSPlayerMovementComponent.generated.h"

/**
 * 
 */
UCLASS(Config = Game)
class RTSMODULERUNTIME_API URTSPlayerMovementComponent : public ULyraCharacterMovementComponent
{
	GENERATED_BODY()
public:

	URTSPlayerMovementComponent(const FObjectInitializer& ObjectInitializer);

};
