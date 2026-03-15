using UnrealBuildTool;

public class fokigaCore: ModuleRules
{
    public fokigaCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine"});
    }
}
