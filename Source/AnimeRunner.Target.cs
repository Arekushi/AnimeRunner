using UnrealBuildTool;
using System.Collections.Generic;

public class AnimeRunnerTarget : TargetRules
{
	public AnimeRunnerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("AnimeRunner");
		bUseUnityBuild = true;
		MinFilesUsingPrecompiledHeader = 1;
	}
}
