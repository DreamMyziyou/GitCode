//
// Created by WeslyChen on 2024/1/19.
//

#include "gtest/gtest.h"
#include "Logger/Logger.h"

TEST(Logger, output)
{
    Logger::LogInfo("LogInfo");
    Logger::Log(Logger::Level::Info, "LoggerTest", "Test Log Info.");
    Logger::Log(Logger::Level::Debug, "LoggerTest", "Test Log Debug.");
    Logger::Log(Logger::Level::Trace, "LoggerTest", "Test Log Trace.");
    Logger::Log(Logger::Level::Warning, "LoggerTest", "Test Log Warning.");
    Logger::Log(Logger::Level::Error, "LoggerTest", "Test Log Error.");
    Logger::Log(Logger::Level::Fatal, "LoggerTest", "Test Log Fatal.");
    EXPECT_TRUE(true);
}