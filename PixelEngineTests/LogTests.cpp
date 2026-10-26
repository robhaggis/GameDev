#include <gtest/gtest.h>

#include <memory>
#include <sstream>

#include <spdlog/sinks/ostream_sink.h>
#include "Pixel/Log.h"

class LogTests : public ::testing::Test
{
protected:
    std::ostringstream engineOutput;
    std::ostringstream appOutput;

    std::shared_ptr<spdlog::logger> previousEngineLogger;
    std::shared_ptr<spdlog::logger> previousAppLogger;

    void SetUp() override
    {
        previousEngineLogger = Pixel::Log::GetEngineLogger();
        previousAppLogger = Pixel::Log::GetAppLogger();

        auto engineSink =
            std::make_shared<spdlog::sinks::ostream_sink_mt>(engineOutput);
        auto appSink =
            std::make_shared<spdlog::sinks::ostream_sink_mt>(appOutput);

        auto engineLogger = std::make_shared<spdlog::logger>("PIXEL-test", engineSink);
        auto appLogger = std::make_shared<spdlog::logger>("APP-test", appSink);

        engineLogger->set_level(spdlog::level::trace);
        appLogger->set_level(spdlog::level::trace);

        Pixel::Log::GetEngineLogger() = engineLogger;
        Pixel::Log::GetAppLogger() = appLogger;
    }

    void TearDown() override
    {
        Pixel::Log::GetEngineLogger() = previousEngineLogger;
        Pixel::Log::GetAppLogger() = previousAppLogger;
    }
};

TEST_F(LogTests, AppMacroWritesToAppLogger)
{
    PIX_INFO("hello {}", "Pixel");

    EXPECT_NE(appOutput.str().find("hello Pixel"), std::string::npos);
    EXPECT_EQ(engineOutput.str().find("hello Pixel"), std::string::npos);
}

TEST_F(LogTests, CoreMacroWritesToEngineLogger)
{
    PIX_CORE_WARN("engine warning");

    EXPECT_NE(engineOutput.str().find("engine warning"), std::string::npos);
    EXPECT_EQ(appOutput.str().find("engine warning"), std::string::npos);
}