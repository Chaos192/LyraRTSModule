// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RTSBasePlayerPawn.h"

ARTSBasePlayerPawn::ARTSBasePlayerPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
}
