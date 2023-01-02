using UnrealBuildTool;
using System.Collections.Generic;

public class AnimeRunnerEditorTarget : TargetRules
{
	public AnimeRunnerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[] { "AnimeRunner" });
	}
}
