
#include "Logger.h"
#include <cstdarg>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/attributes/constant.hpp>


using namespace mikasa::Runtime::Foundation;

src::severity_logger_mt<logging::trivial::severity_level> Logger::logger_;

const int MAX_LOG_LEN = 2048;

void Logger::Init(uint64 sinkMode, const std::string& target, const std::string& fileName)
{
    InitLoggingCore();
    InitSink(sinkMode, target, fileName);
}

void Logger::InitLoggingCore()
{
    logging::add_common_attributes();
    logger_.add_attribute("Tag", attrs::constant<std::string>("Engine"));
}

void Logger::InitSink(uint64 sinkMode, const std::string& target, const std::string& fileName)
{
    // formatter
    logging::formatter formatter = expr::format("[%1%][%2%][%3%] - %4%")
                                   % expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
                                   % logging::trivial::severity
                                   % expr::attr<std::string>("Tag")
                                   % expr::message;

    // console
    if (sinkMode & 0x1)
    {
        auto consoleSink = logging::add_console_log(std::cout);
        consoleSink->set_formatter(formatter);
        consoleSink->set_filter(logging::trivial::severity >= logging::trivial::debug);
    }

    // file
    if (sinkMode & 0x10)
    {
        auto fileSink = logging::add_file_log(
                keywords::open_mode = std::ios_base::app,
                keywords::target = target,
                keywords::file_name = fileName
        );

        fileSink->set_formatter(formatter);
        fileSink->set_filter(logging::trivial::severity >= logging::trivial::debug);
        fileSink->locked_backend()->auto_flush();
    }
}

void Logger::UnInit()
{

}

void Logger::Warning(const char* const format, ...)
{
    char Buffer_[MAX_LOG_LEN];
    va_list args;
            va_start(args, format);
    vsnprintf(Buffer_, MAX_LOG_LEN, format, args);
            va_end(args);

    BOOST_LOG_SEV(logger_, logging::trivial::severity_level::warning) << Buffer_;
}

void Logger::Error(const char* const format, ...)
{
    char Buffer_[MAX_LOG_LEN];
    va_list args;
            va_start(args, format);
    vsnprintf(Buffer_, MAX_LOG_LEN, format, args);
            va_end(args);

    BOOST_LOG_SEV(logger_, logging::trivial::severity_level::error) << Buffer_;
}

void Logger::Info(const char* const format, ...)
{
    // buffer must on stack to keep logger thread safe.
    char Buffer_[MAX_LOG_LEN];
    va_list args;
            va_start(args, format);
    vsnprintf(Buffer_, MAX_LOG_LEN, format, args);
            va_end(args);

    BOOST_LOG_SEV(logger_, logging::trivial::severity_level::info) << Buffer_;
}

void Logger::Debug(const char* const format, ...)
{
    char Buffer_[MAX_LOG_LEN];
    va_list args;
            va_start(args, format);
    vsnprintf(Buffer_, MAX_LOG_LEN, format, args);
            va_end(args);

    BOOST_LOG_SEV(logger_, logging::trivial::severity_level::debug) << Buffer_;
}