project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    
    targetdir ("bin/" .. outputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    sysincludedirs
    {
        "include"
    }
    
    filter "system:windows"
        systemversion "latest"

    filter "system:darwin"
        systemversion "latest"
	xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
