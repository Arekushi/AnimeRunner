// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AnimeRunner : ModuleRules
{
	public AnimeRunner(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Paper2D"
		});

		MinFilesUsingPrecompiledHeaderOverride = 1;
 		bUseUnity = false;
	}
}
