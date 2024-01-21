//
// Created by WeslyChen on 2024/1/19.
//

#include "Logger.h"

#include "LoggerModule.h"

void Logger::WakeUp()
{
    LoggerModule::instance();
}

void Logger::EnableLogger()
{
    LoggerModule::instance()->SetEnabled(true);
}

void Logger::DisableLogger()
{
    LoggerModule::instance()->SetEnabled(false);
}

void Logger::Log(Logger::Level level, const String& module, const String& message)
{
    LoggerModule::instance()->Log(level, module, message);
}

void Logger::LogInfo(const String& module, const String& message)
{
    LoggerModule::instance()->Log(Logger::Level::Info, module, message);
}

void Logger::LogInfo(const String& message)
{
    LoggerModule::instance()->Log(Logger::Level::Info, Logger::DEFAULT_MODULE_NAME, message);
}
