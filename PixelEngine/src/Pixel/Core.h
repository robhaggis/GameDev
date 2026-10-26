#pragma once
#include <cstdint>

#ifdef PIXEL_PLATFORM_WINDOWS
	#ifdef PIXEL_BUILD_DLL
		#define PIXEL_API __declspec(dllexport)
	#else
		#define PIXEL_API __declspec(dllimport)
	#endif
#else
	#error PixelEngine is only supported on windows
#endif

#ifdef PIXEL_PLATFORM_WINDOWS
#define PIX_CORE_ASSERT(x, ...) { if(!(x)) { PIX_CORE_FATAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define PIX_ASSERT(x, ...) { if(!(x)) { PIX_FATAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#endif

//Macros
#define KILOBYTES(value) ((value)*1024LL)
#define MEGABYTES(value) (KILOBYTES(value)*1024LL)
#define GIGABYTES(value) (MEGABYTES(value)*1024LL)
#define TERABYTES(value) (GIGABYTES(value)*1024LL)
//Typedefs
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t ui8;
typedef uint16_t ui16;
typedef uint32_t ui32;
typedef uint64_t ui64;

typedef float f32;
typedef double f64;

constexpr f64 PI = 3.14159265358979323846;
