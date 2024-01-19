//
// Created by WeslyChen on 2024/1/19.
//

#include "LoggerModule.h"

#include "boost/log/core.hpp"
#include "boost/log/trivial.hpp"

using namespace std;
using namespace Logger;

void LoggerModule::StartupModule()
{
    IModule::StartupModule();
}

void LoggerModule::ShutdownModule()
{
    IModule::ShutdownModule();
}

void LoggerModule::Log(Logger::Level level, const String& module, const String& message)
{
    switch (level)
    {
        case Level::Info:
            BOOST_LOG_TRIVIAL(info) << "[" << module << "]" << message;
            break;
        case Level::Debug:
            BOOST_LOG_TRIVIAL(debug) << "[" << module << "]" << message;
            break;
        case Level::Trace:
            BOOST_LOG_TRIVIAL(trace) << "[" << module << "]" << message;
            break;
        case Level::Warning:
            BOOST_LOG_TRIVIAL(warning) << "[" << module << "]" << message;
            break;
        case Level::Error:
            BOOST_LOG_TRIVIAL(error) << "[" << module << "]" << message;
            break;
        case Level::Fatal:
            BOOST_LOG_TRIVIAL(fatal) << "[" << module << "]" << message;
            break;
        default:
            break;
    }
}
