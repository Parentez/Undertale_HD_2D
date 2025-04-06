// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Undertale_HD_2D : ModuleRules
{
	public Undertale_HD_2D(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });
	}
}
