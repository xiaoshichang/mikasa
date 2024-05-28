#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>

#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>

#include <boost/log/expressions.hpp>
#include <boost/log/expressions/formatters/stream.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>

#include <boost/log/trivial.hpp>
#include <boost/log/support/date_time.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "Runtime/Foundation/Foundation.h"

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

namespace mikasa::Runtime::Foundation
{
    enum LogSink
    {
        Console = 1,
        File = 1 << 1,
    };

    class Logger
    {
    public:
        static void Init(uint64 sinkMode, const std::string& target, const std::string& fileName);
        static void UnInit();

    private:
        static void InitLoggingCore();
        static void InitSink(uint64 sinkMode, const std::string& target, const std::string& fileName);

    public:
        static void Error(const char* format, ...);
        static void Warning(const char* format, ...);
        static void Info(const char* format, ...);
        static void Debug(const char* format, ...);

    private:
        static src::severity_logger_mt<logging::trivial::severity_level> logger_;
    };
}


