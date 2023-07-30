// © 2023 Kaya Adrian.

using UnrealBuildTool;


// ReSharper disable once InconsistentNaming
public class AtumEditor : ModuleRules
{
	public AtumEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.CPlusPlus;
		PCHUsage = PCHUsageMode.NoPCHs;
		IWYUSupport = IWYUSupport.Full;
		CppStandard = CppStandardVersion.Cpp20;
		
		bUseRTTI = true;
		bUseUnity = false;
		bUsePrecompiled = false;
		bEnableExceptions = true;
		
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Atum",
			"Core",
			"CoreUObject"
		});
		
		PrivateDependencyModuleNames.AddRange(new[]
		{
			"AssetTools",
			"GraphEditor",
			"Slate",
			"SlateCore",
			"UnrealEd"
		});
	}
}
