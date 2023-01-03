// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "ModularPawn.h"
#include "RTSPlayerHeroComponent.h"
#include "Character/LyraHeroComponent.h"
#include "Character/LyraHealthComponent.h"
#include "Character/LyraPawnExtensionComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/LyraCameraComponent.h"
#include "Character/LyraCharacter.h"
#include "Teams/LyraTeamAgentInterface.h"
#include "AbilitySystemInterface.h"
#include "GameplayCueInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/SpringArmComponent.h"
#include "RTSSelectionHandlerComponent.h"
#include "RTSPlayerMovementComponent.h"
#include "RTSBasePlayerPawn.generated.h"

class AActor;
class AController;
class ALyraPlayerController;
class ALyraPlayerState;
class FLifetimeProperty;
class IRepChangedPropertyTracker;
class UAbilitySystemComponent;
class UInputComponent;
class ULyraAbilitySystemComponent;
class ULyraCameraComponent;
class ULyraHealthComponent;
class ULyraPawnExtensionComponent;
class UObject;
struct FFrame;
struct FGameplayTag;
struct FGameplayTagContainer;
class URTSPlayerHeroComponent;

/**
 * Lyra RTS Pawn
 * require code change to LyraPawn.h to expose ALyraPawn class
 * require code change to LyraPawnExtensionComponent.h to expose ULyraPawnExtensdionComponent class
 * * require code change to LyraAbilitySystemComponent.h to expose ULyraAbilitySystemComponent class
 * TODO: lessen depedency on these class
 */
UCLASS(Config = Game, Meta = (ShortTooltip = "The base character pawn class used by this project."))
class RTSMODULERUNTIME_API ARTSBasePlayerPawn : public ALyraCharacter
{
	GENERATED_BODY()
	
public:
	ARTSBasePlayerPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
