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


IncludeDir = {}
IncludeDir["GLFW"] = "PixelEngine/thirdparty/GLFW/include"
IncludeDir["Glad"] = "PixelEngine/thirdparty/glad"
IncludeDir["KHR"] = "PixelEngine/thirdparty/"

LibDir = {}
LibDir["GLFW"] = "PixelEngine/thirdparty/GLFW/bin/Debug-windows-x86_64/GLFW"

project "GLAD"
	location "PixelEngine/thirdparty/glad"
	kind "StaticLib"
	language "C"
	cdialect "C17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"PixelEngine/thirdparty/glad/glad.c",
	}

	includedirs
	{
		"PixelEngine/thirdparty/glad",
		"PixelEngine/thirdparty"
	}

	filter "system:windows"
	systemversion "latest"
	staticruntime "On"

	filter "configurations:Debug"
		symbols "On"
		optimize "Off"

	filter "configurations:Release"
		symbols "On"
		optimize "On"

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
		"%{prj.name}/thirdparty/glad",
		"%{IncludeDir.KHR}",
		"%{IncludeDir.GLFW}",
	}

	libdirs
	{
		"%{LibDir.GLFW}"
	}

	links
	{
		"GLAD",
		"GLFW",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
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
		buildoptions "/MDd"
		symbols "On"
		optimize "Off"
		libdirs
		{
			"PixelEngine/thirdparty/GLFW/bin/Release-windows-x86_64/GLFW"
		}

	filter "configurations:Release"
		defines
		{
			"PIXEL_RELEASE"
		}
		buildoptions "/MD"
		symbols "On"
		optimize "On"
		libdirs
		{
			"PixelEngine/thirdparty/GLFW/bin/Release-windows-x86_64/GLFW"
		}

	filter "configurations:Distro"
		defines
		{
			"PIXEL_DISTRO"
		}
		buildoptions "/MD"
		symbols "Off"
		optimize "On"
		libdirs
		{
			"PixelEngine/thirdparty/GLFW/bin/Release-windows-x86_64/GLFW"
		}

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
		"PixelEngine/src",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.KHR}",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"PixelEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
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
		buildoptions "/MDd"
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