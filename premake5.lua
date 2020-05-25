workspace "Chickenkiller"
	architecture "x86_64"
	startproject "Chickenkiller"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	flags {
		"MultiProcessorCompile"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Asylum/vendor/GLFW/include"
IncludeDir["Glad"] = "Asylum/vendor/Glad/include"
IncludeDir["glm"] = "Asylum/vendor/glm"
IncludeDir["stb_image"] = "Asylum/vendor/stb_image"
IncludeDir["json"] = "Asylum/vendor/json/include"
IncludeDir["ImGui"] = "Asylum/vendor/imgui"

group "Dependencies"
	include "Asylum/vendor/GLFW"
	include "Asylum/vendor/Glad"
	include "Asylum/vendor/imgui"

group ""

project "Asylum"
	location "Asylum"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "src/ampch.h"
	pchsource "Asylum/src/ampch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/json/**.h"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
	}

	sysincludedirs {
		"%{prj.name}/",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.json}",
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"AM_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "system:darwin"
		systemversion "latest"
		xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }		
		defines {
			"AM_PLATFORM_DARWIN",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "AM_DEBUG"
		runtime "Debug"
		symbols "on"

		includedirs {
			"%{prj.name}/",
			"%{prj.name}/src",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb_image}",
			"%{IncludeDir.json}",
			"%{IncludeDir.ImGui}"
		}

		links { 
			"GLFW",
			"Glad",
			"opengl32.lib",
			"ImGui"
		}

	filter "configurations:Release"
		defines "AM_RELEASE"
		runtime "Release"
		optimize "on"

		sysincludedirs {
			"%{prj.name}/",
			"%{prj.name}/src",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb_image}",
			"%{IncludeDir.json}",
		}

		links { 
			"GLFW",
			"Glad",
			"opengl32.lib"
		}

	filter "configurations:Dist"
		defines "AM_DIST"
		runtime "Release"
		optimize "on"

		sysincludedirs {
			"%{prj.name}/",
			"%{prj.name}/src",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb_image}",
			"%{IncludeDir.json}",
		}

		links { 
			"GLFW",
			"Glad",
			"opengl32.lib"
		}

project "Chickenkiller"
	location "Chickenkiller"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	sysincludedirs {
		"Asylum/src",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.json}"
	}

	links {
		"GLFW",
		"Asylum"
	}

	filter "system:windows"
		systemversion "latest"
		defines {
			"AM_PLATFORM_WINDOWS"
		}

	filter "system:darwin"
		systemversion "latest"
		links { "Cocoa.framework", "CoreVideo.framework", "IOKit.framework" }
		xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }
		defines {
			"AM_PLATFORM_DARWIN"
		}

	filter "configurations:Debug"
		defines "AM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AM_RELEASE"
		kind "WindowedApp"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AM_DIST"
		kind "WindowedApp"
		runtime "Release"
		optimize "on"
