// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RTSModuleRuntime : ModuleRules
{
	public RTSModuleRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"LyraGame",
				"ModularGameplay",
				"ModularGameplayActors",
				"CommonGame",
				"GameplayTags"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{

                "CoreUObject",
				"Engine",
                "Slate",
                "SlateCore",
				"GameplayTags",
				"GameplayTasks",
				"GameplayAbilities",
				"GameplayMessageRuntime",
				"AIModule",
				"Niagara",
				"CommonUser",
				"CommonUI",
				"CommonInput",
				"NetworkReplayStreaming",
				"DataRegistry",
				"UIExtension",
				"ClientPilot",
				"InputCore",
				"RenderCore",
				"DeveloperSettings",
				"EnhancedInput",
				"NetCore",
				"RHI",
				"Projects",
				"UMG",
				"GameplayMessageRuntime",
				"AudioMixer",
				"NetworkReplayStreaming",
				"UIExtension",
				"ClientPilot"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
