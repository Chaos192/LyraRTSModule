// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "ModularPawn.h"
#include "RTSCamera.h"
#include "Character/LyraHeroComponent.h"
#include "Character/LyraPawnExtensionComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/LyraCameraComponent.h"
#include "Character/LyraPawn.h"
#include "Teams/LyraTeamAgentInterface.h"
#include "AbilitySystemInterface.h"
#include "GameplayCueInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/SpringArmComponent.h"
#include "RTSBasePlayerPawn.generated.h"


/**
 * Lyra RTS Pawn
 * require code change to LyraPawn.h to expose ALyraPawn class
 * require code change to LyraPawnExtensionComponent.h to expose ULyraPawnExtensdionComponent class
 * * require code change to LyraAbilitySystemComponent.h to expose ULyraAbilitySystemComponent class
 * TODO: lessen depedency on these class
 */
UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class RTSMODULERUNTIME_API ARTSBasePlayerPawn : public ALyraPawn, public IAbilitySystemInterface, public IGameplayCueInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	

public:

	ARTSBasePlayerPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Lyra|Pawn")
		ULyraAbilitySystemComponent* GetLyraAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
protected:

	virtual void OnAbilitySystemInitialized();
	virtual void OnAbilitySystemUninitialized();
	void InitializeGameplayTags();
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RTS|Pawn", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<ULyraPawnExtensionComponent> PawnExtComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RTS|Pawn", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<ULyraHeroComponent> LyraHeroComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RTS|Pawn", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<ULyraCameraComponent> CameraComponent;
	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category = "RTS|Pawn", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USceneComponent> SceneRootComponent;

	UPROPERTY(Category = "RTS|Pawn", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(Category = "RTS|Pawn", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<URTSCamera> RTSCamera;
};
