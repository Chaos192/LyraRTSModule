// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "UObject/UObjectGlobals.h"
#include "GameplayTagContainer.h"

#include "StrategyResources.generated.h"

USTRUCT(BlueprintType)
struct RTSMODULERUNTIME_API FStrategyResource
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FName Name;

	UPROPERTY(EditAnywhere)
		float Amount;

	UPROPERTY(EditAnywhere)
		float Min;

	UPROPERTY(EditAnywhere)
		float Max;
};

UCLASS(BlueprintType)
class RTSMODULERUNTIME_API UStrategyResourceData: public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FText Description=FText::GetEmpty();

	UPROPERTY(EditAnywhere)
		FStrategyResource Resource;
};

USTRUCT(BlueprintType)
struct RTSMODULERUNTIME_API FStrategyResourceConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TObjectPtr<const UStrategyResourceData> ResourceData;

	UPROPERTY(EditAnywhere)
		FGameplayTag ResourceTag;
};

UCLASS(BlueprintType)
class RTSMODULERUNTIME_API UStrategyResourcesConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<FStrategyResourceConfig> ResourcesConfig;

};

USTRUCT(BlueprintType)
struct RTSMODULERUNTIME_API FStrategyResourceInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		FGameplayTag ResourceTag;
	UPROPERTY(EditAnywhere)
		float Quantity;
	UPROPERTY(EditAnywhere)
		int Quality;
};

UCLASS(BlueprintType)
class RTSMODULERUNTIME_API UStrategyResourcesConversionMapping : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<FStrategyResourceInfo> RequiredResources;

	UPROPERTY(EditAnywhere)
		TArray<FStrategyResourceInfo> GeneratedResources;

	UPROPERTY(EditAnywhere)
		FGameplayTagContainer GenerationRequiredTag;

	UPROPERTY(EditAnywhere)
		FGameplayTagContainer GenerationBlockedTag;
};

UCLASS(BlueprintType)
class RTSMODULERUNTIME_API UStrategyResourcesGameData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<FStrategyResourceInfo> StartAvailableResources;

	UPROPERTY(EditAnywhere)
		TArray<FStrategyResourceInfo> AutoGenerateResources;

	UPROPERTY(EditAnywhere)
		TArray<TObjectPtr<const UStrategyResourcesConversionMapping>> ResourceConversionMappings;

};