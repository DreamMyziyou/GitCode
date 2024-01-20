//
// Created by WeslyChen on 2024/1/19.
//

#ifndef WORKENGINE_LOGGERMODULE_H
#define WORKENGINE_LOGGERMODULE_H

#include "Common/ClassMacro.h"
#include "Logger.h"

class LoggerModule final
{
    SINGLETON_CLASS_CUSTOM_CONSTRUCT(LoggerModule)

public:
    void SetEnabled(bool isEnabled) { mIsEnabled = isEnabled; }

    void Log(Logger::Level level, const String& module, const String& message);

private:
    struct Impl;
    Impl* mImpl = nullptr;

    bool mIsEnabled = true;
};

#endif  // WORKENGINE_LOGGERMODULE_H
