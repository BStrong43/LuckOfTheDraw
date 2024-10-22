// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LOTD : ModuleRules
{
	public LOTD(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {"EnhancedInput", "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
