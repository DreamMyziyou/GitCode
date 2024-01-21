//
// Created by WeslyChen on 2024/1/19.
//

#ifndef WORKENGINE_LOGGER_H
#define WORKENGINE_LOGGER_H

#include "Core/BasicType/BasicType.h"
#include "Core/BasicType/String.h"
#include "LoggerExport.h"

namespace Logger
{
    enum class Level : uint8
    {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
        Default = Info,
    };

    constexpr const char* DEFAULT_MODULE_NAME = "Global";

    LOGGER_API void WakeUp();
    LOGGER_API void EnableLogger();
    LOGGER_API void DisableLogger();

    LOGGER_API void Log(Level level, const String& module, const String& message);
    LOGGER_API void LogInfo(const String& module, const String& message);
    LOGGER_API void LogInfo(const String& message);

}  // namespace Logger

#endif  // WORKENGINE_LOGGER_H
