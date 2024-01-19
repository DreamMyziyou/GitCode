//
// Created by WeslyChen on 2024/1/19.
//

#ifndef WORKENGINE_LOGGERMODULE_H
#define WORKENGINE_LOGGERMODULE_H

#include "Logger.h"
#include "Module/ModuleSingleton.h"

class LoggerModule final : public Module::IModule
{
    SINGLETON_MODULE(LoggerModule)

public:
    void StartupModule() override;
    void ShutdownModule() override;

public:
    void Log(Logger::Level level, const String& module, const String& message);
};

#endif  // WORKENGINE_LOGGERMODULE_H
