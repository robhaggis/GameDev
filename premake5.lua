workspace "GameDev"
	architecture "x64"
	startproject "PixelSandbox"

	configurations
	{
		"Debug",
		"Release",
		"Distro"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "PixelEngine"
	location "PixelEngine"
	kind "SharedLib"
	language "C++"
	characterset "Unicode"
	buildoptions{"/utf-8"}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "PixelPCH.h"
	pchsource "PixelEngine/src/PixelPCH.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/thirdparty/spdlog/include",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PIXEL_PLATFORM_WINDOWS",
			"PIXEL_BUILD_DLL",
		}

		postbuildcommands
		{
			
			("copy /B /Y ..\\bin\\" .. outputdir .. "\\PixelEngine\\PixelEngine.dll ..\\bin\\" .. outputdir .. "\\PixelSandbox\\ > nul")
		}
	
	filter "configurations:Debug"
		defines
		{
			"PIXEL_DEBUG"
		}
		symbols "On"
		optimize "Off"

	filter "configurations:Release"
		defines
		{
			"PIXEL_RELEASE"
		}
		symbols "On"
		optimize "On"

	filter "configurations:Distro"
		defines
		{
			"PIXEL_DISTRO"
		}
		symbols "Off"
		optimize "On"


project "PixelSandbox"
	location "PixelSandbox"
	kind "ConsoleApp"
	language "C++"
	characterset "Unicode"
	buildoptions{"/utf-8"}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"PixelEngine/thirdparty/spdlog/include",
		"PixelEngine/src"
	}

	links
	{
		"PixelEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PIXEL_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines
		{
			"PIXEL_DEBUG"
		}
		symbols "On"
		optimize "Off"

	filter "configurations:Release"
		defines
		{
			"PIXEL_RELEASE"
		}
		symbols "On"
		optimize "On"

	filter "configurations:Distro"
		defines
		{
			"PIXEL_DISTRO"
		}
		symbols "Off"
		optimize "On"



