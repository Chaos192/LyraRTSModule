// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RTSBasePlayerPawn.h"
#include "LyraLogChannels.h"
#include "Character/LyraPawnExtensionComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/ActorComponent.h"
#include "Camera/LyraCameraComponent.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "Character/LyraHealthComponent.h"
#include "Player/LyraPlayerController.h"
#include "Player/LyraPlayerState.h"
#include "System/LyraSignificanceManager.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"

ARTSBasePlayerPawn::ARTSBasePlayerPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(ACharacter::CapsuleComponentName);
	//CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
	//CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	//CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	//CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	//CapsuleComponent->SetCanEverAffectNavigation(false);
	//CapsuleComponent->bDynamicObstacle = true;
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneRootComponent;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	PawnExtComponent = CreateDefaultSubobject<ULyraPawnExtensionComponent>(TEXT("LyraPawnExtensionComponent"));
	PawnExtComponent->OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnAbilitySystemInitialized));
	PawnExtComponent->OnAbilitySystemUninitialized_Register(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnAbilitySystemUninitialized));

	LyraHeroComponent = CreateDefaultSubobject<ULyraHeroComponent>(TEXT("LyraHeroComponent"));

	CameraComponent = CreateDefaultSubobject<ULyraCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);
	// CameraComponent->SetRelativeLocation(FVector(-300.0f, 0.0f, 75.0f));
	RTSCamera = CreateDefaultSubobject<URTSCamera>(TEXT("RTSCameraComponent"));

}

ULyraAbilitySystemComponent* ARTSBasePlayerPawn::GetLyraAbilitySystemComponent() const
{
	return Cast<ULyraAbilitySystemComponent>(GetAbilitySystemComponent());
}

UAbilitySystemComponent* ARTSBasePlayerPawn::GetAbilitySystemComponent() const
{
	return PawnExtComponent->GetLyraAbilitySystemComponent();
}

void ARTSBasePlayerPawn::OnAbilitySystemInitialized()
{
	ULyraAbilitySystemComponent* LyraASC = GetLyraAbilitySystemComponent();
	check(LyraASC);

	InitializeGameplayTags();
}

void ARTSBasePlayerPawn::OnAbilitySystemUninitialized()
{
}

void ARTSBasePlayerPawn::InitializeGameplayTags()
{
	// Clear tags that may be lingering on the ability system from the previous pawn.
	//if (ULyraAbilitySystemComponent* LyraASC = GetLyraAbilitySystemComponent())
	//{
	//}
}

void ARTSBasePlayerPawn::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (const ULyraAbilitySystemComponent* LyraASC = GetLyraAbilitySystemComponent())
	{
		LyraASC->GetOwnedGameplayTags(TagContainer);
	}
}

bool ARTSBasePlayerPawn::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	if (const ULyraAbilitySystemComponent* LyraASC = GetLyraAbilitySystemComponent())
	{
		return LyraASC->HasMatchingGameplayTag(TagToCheck);
	}

	return false;
}

bool ARTSBasePlayerPawn::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	if (const ULyraAbilitySystemComponent* LyraASC = GetLyraAbilitySystemComponent())
	{
		return LyraASC->HasAllMatchingGameplayTags(TagContainer);
	}

	return false;
}

bool ARTSBasePlayerPawn::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	if (const ULyraAbilitySystemComponent* LyraASC = GetLyraAbilitySystemComponent())
	{
		return LyraASC->HasAnyMatchingGameplayTags(TagContainer);
	}

	return false;
}
