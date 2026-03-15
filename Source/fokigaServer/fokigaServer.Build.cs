using UnrealBuildTool;

public class fokigaServer: ModuleRules
{
    public fokigaServer(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine"});
    }
}
