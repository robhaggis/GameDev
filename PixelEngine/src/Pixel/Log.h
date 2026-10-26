#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Pixel
{
	class PIXEL_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger(){ return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
	};
}


//TODO Strip these macros from distribution builds
#define PIX_CORE_TRACE(...) ::Pixel::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define PIX_CORE_INFO(...)  ::Pixel::Log::GetEngineLogger()->info(__VA_ARGS__)
#define PIX_CORE_WARN(...)  ::Pixel::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define PIX_CORE_ERROR(...) ::Pixel::Log::GetEngineLogger()->error(__VA_ARGS__)
#define PIX_CORE_FATAL(...) ::Pixel::Log::GetEngineLogger()->critical(__VA_ARGS__)

#define PIX_TRACE(...)      ::Pixel::Log::GetAppLogger()->trace(__VA_ARGS__)
#define PIX_INFO(...)       ::Pixel::Log::GetAppLogger()->info(__VA_ARGS__)
#define PIX_WARN(...)       ::Pixel::Log::GetAppLogger()->warn(__VA_ARGS__)
#define PIX_ERROR(...)      ::Pixel::Log::GetAppLogger()->error(__VA_ARGS__)
#define PIX_FATAL(...)      ::Pixel::Log::GetAppLogger()->critical(__VA_ARGS__)



