// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPS_205 : ModuleRules
{
	public FPS_205(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara" });
	}
}
