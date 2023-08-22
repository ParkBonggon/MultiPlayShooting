// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShootingGameCode : ModuleRules
{
	public ShootingGameCode(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", 
			"Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", 
			"UMG", "ItemPlugin", "OnlineSubsystem", "OnlineSubsystemUtils" });

		PublicIncludePaths.AddRange(new string[] { "ShootingGameCode", "ShootingGameCode/Public", "ShootingGameCode/Public/Lobby" });

		PrivateIncludePaths.AddRange(new string[] { "ShootingGameCode/Private", "ShootingGameCode/Private/Lobby" });

        DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
    }
}
