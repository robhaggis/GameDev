#pragma once

#ifdef PIXEL_PLATFORM_WINDOWS
	#ifdef PIXEL_BUILD_DLL
		#define PIXEL_API __declspec(dllexport)
	#else
		#define PIXEL_API __declspec(dllimport)
	#endif
#else
	#error PixelEngine is only supported on windows
#endif

