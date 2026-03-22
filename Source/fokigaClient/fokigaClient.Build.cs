using UnrealBuildTool;

public class fokigaClient: ModuleRules
{
    public fokigaClient(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "UMG"});
    }
}
