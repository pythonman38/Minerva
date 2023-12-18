// Midnight Madness Inc.

using UnrealBuildTool;
using System.Collections.Generic;

public class MinervaEditorTarget : TargetRules
{
	public MinervaEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Minerva" } );
	}
}
