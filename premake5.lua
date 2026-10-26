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

project "PixelEngineTests"
	kind "ConsoleApp"
	language "C++"
	characterset "Unicode"
	buildoptions { "/utf-8" }

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"PixelEngineTests/**.h",
		"PixelEngineTests/**.cpp"
	}

	includedirs
	{
		"PixelEngine/src",
		"PixelEngine/thirdparty/googletest/googletest/include",
		"PixelEngine/thirdparty/spdlog/include"
	}

	links
	{
		"PixelEngine",
		"GoogleTest"
	}

	postbuildcommands
	{
		("copy /B /Y bin\\" .. outputdir .. "\\PixelEngine\\PixelEngine.dll bin\\" .. outputdir .. "\\PixelEngineTests\\ > nul")
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

filter {}

project "GoogleTest"
    location "PixelEngine/thirdparty/googletest"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "PixelEngine/thirdparty/googletest/googletest/src/gtest-all.cc",
        "PixelEngine/thirdparty/googletest/googletest/src/gtest_main.cc"
    }

    includedirs
    {
        "PixelEngine/thirdparty/googletest/googletest",
        "PixelEngine/thirdparty/googletest/googletest/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        symbols "On"
        optimize "Off"

    filter "configurations:Release"
        symbols "On"
        optimize "On"

    filter "configurations:Distro"
        symbols "Off"
        optimize "On"

