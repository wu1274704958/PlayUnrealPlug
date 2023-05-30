// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestPlug : ModuleRules
{
	public TestPlug(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","RHI" });

		PrivateDependencyModuleNames.AddRange(new string[] { "RenderCore" });
		
		PublicIncludePaths.AddRange(new string[]
		{
			"TestPlug/CustomComponent/Classes"
		});
		PrivateIncludePaths.AddRange(new string[]
		{
			"TestPlug"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
