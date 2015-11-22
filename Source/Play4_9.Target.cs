// Temp

using UnrealBuildTool;
using System.Collections.Generic;

public class Play4_9Target : TargetRules
{
	public Play4_9Target(TargetInfo Target)
	{
		Type = TargetType.Game;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] { "Play4_9" } );
	}
}
