// Midnight Madness Inc.

using UnrealBuildTool;
using System.Collections.Generic;

public class MinervaTarget : TargetRules
{
	public MinervaTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Minerva" } );
	}
}
