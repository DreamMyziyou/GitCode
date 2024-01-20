//
// Created by WeslyChen on 2024/1/19.
//

#include "LoggerModule.h"

#include <boost/log/core.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/trivial.hpp>

#include "Common/DeleteMacro.h"

using namespace std;
using namespace boost::log;

struct LoggerModule::Impl
{
    sources::severity_logger_mt<boost::log::trivial::severity_level> logger;
};

LoggerModule::LoggerModule()
{
    // log output to file
    // add_file_log("Logger.log");

    // filter level
    // core::get()->set_filter(trivial::severity >= trivial::info);

    mImpl = new LoggerModule::Impl();
}

LoggerModule::~LoggerModule()
{
    SAFE_DELETE(mImpl);
}

void LoggerModule::Log(Logger::Level level, const String& module, const String& message)
{
    switch (level)
    {
        case Logger::Level::Trace:
            BOOST_LOG_SEV(mImpl->logger, trivial::trace) << "[" << module << "] " << message;
            break;
        case Logger::Level::Debug:
            BOOST_LOG_SEV(mImpl->logger, trivial::debug) << "[" << module << "] " << message;
            break;
        case Logger::Level::Info:
            BOOST_LOG_SEV(mImpl->logger, trivial::info) << "[" << module << "] " << message;
            break;
        case Logger::Level::Warning:
            BOOST_LOG_SEV(mImpl->logger, trivial::warning) << "[" << module << "] " << message;
            break;
        case Logger::Level::Error:
            BOOST_LOG_SEV(mImpl->logger, trivial::error) << "[" << module << "] " << message;
            break;
        case Logger::Level::Fatal:
            BOOST_LOG_SEV(mImpl->logger, trivial::fatal) << "[" << module << "] " << message;
            break;
        default:
            break;
    }
}
