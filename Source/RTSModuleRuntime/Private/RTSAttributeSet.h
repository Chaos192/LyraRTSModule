// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attributes/LyraAttributeSet.h"
#include "NativeGameplayTags.h"
#include "RTSAttributeSet.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class RTSMODULERUNTIME_API URTSAttributeSet : public ULyraAttributeSet
{
	GENERATED_BODY()
public:
	URTSAttributeSet();

	const float MAXPOPULATION = 1000.0f;
	const float MAXMINERAL = 9999.0f;
	const float MAXGAS = 9999.0f;


	ATTRIBUTE_ACCESSORS(ThisClass, Population);
	ATTRIBUTE_ACCESSORS(ThisClass, Mineral);
	ATTRIBUTE_ACCESSORS(ThisClass, Gas);

	//~UAttributeSet interface
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	//~End of UAttributeSet interface
protected:

	UFUNCTION()
		void OnRep_Population(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		void OnRep_Mineral(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		void OnRep_Gas(const FGameplayAttributeData& OldValue);

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;
private:
	// The number of bombs remaining
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Population, Category = "RTSGame", Meta = (AllowPrivateAccess = true))
		FGameplayAttributeData Population;

	// The maximum number of bombs that can be placed at once
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mineral, Category = "RTSGame", Meta = (AllowPrivateAccess = true))
		FGameplayAttributeData Mineral;

	// The range/radius of bomb blasts
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Gas, Category = "RTSGame", Meta = (AllowPrivateAccess = true))
		FGameplayAttributeData Gas;

};
