// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Containers/UnrealString.h"
#include "Logging/LogMacros.h"

class UObject;

RTSMODULERUNTIME_API DECLARE_LOG_CATEGORY_EXTERN(LogRTS, Log, All);
RTSMODULERUNTIME_API DECLARE_LOG_CATEGORY_EXTERN(LogRTSExperience, Log, All);

class FRTSModuleRuntimeModule : public IModuleInterface
{
public:
	//~IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//~End of IModuleInterface
};
