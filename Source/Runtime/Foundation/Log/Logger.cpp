
#include "Logger.h"
#include <cstdarg>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/attributes/constant.hpp>
#include "ConsoleSink.h"


using namespace mikasa::Runtime::Foundation;

src::severity_logger_mt<logging::trivial::severity_level> Logger::logger_;
src::severity_logger_mt<logging::trivial::severity_level> Logger::ScriptLogger_;

const int MAX_LOG_LEN = 2048;
BOOST_LOG_ATTRIBUTE_KEYWORD(a_thread_name, "ThreadName", std::string)

void Logger::Init(uint64 sinkMode, const std::string& target, const std::string& fileName)
{
    InitLoggingCore();
    InitSink(sinkMode, target, fileName);
}

void Logger::InitLoggingCore()
{
    logging::add_common_attributes();
    boost::log::core::get()->add_thread_attribute("ThreadName", boost::log::attributes::constant< std::string >("Main"));
    logger_.add_attribute("Tag", attrs::constant<std::string>("Engine"));
    ScriptLogger_.add_attribute("Tag", attrs::constant<std::string>("Script"));
}

void Logger::InitSink(uint64 sinkMode, const std::string& target, const std::string& fileName)
{
    if (sinkMode & LogSink::ConsoleBackend)
    {
        InitConsoleSink();
    }
    if (sinkMode & LogSink::FileBackend)
    {
        InitFileSink(target, fileName);
    }
}

void Logger::InitConsoleSink()
{
    typedef sinks::unlocked_sink<ConsoleSink> sink_t;
    boost::shared_ptr< sink_t > sink(new sink_t());

    auto formatter =
            expr::stream
                    << '[' << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S") << ']'
                    << '[' << std::setw(7)<< logging::trivial::severity << ']'
                    << '[' << std::setw(8) << expr::attr<std::string>("Tag") << ']'
                    //<< '[' << expr::attr <boost::log::attributes::current_thread_id::value_type> ("ThreadID") << ']'
                    << '[' << std::setw(8) << a_thread_name << ']'
                    << " - " << expr::message;

    boost::shared_ptr< logging::core > core = logging::core::get();
    core->add_sink(sink);
    sink->set_formatter(formatter);
    sink->set_filter(logging::trivial::severity >= logging::trivial::debug);

//    auto consoleSink = logging::add_console_log(std::cout);
//    consoleSink->set_formatter(formatter);
//    consoleSink->set_filter(logging::trivial::severity >= logging::trivial::debug);
}

void Logger::InitFileSink(const std::string &target, const std::string &fileName)
{
    auto formatter =
            expr::stream
                    << '[' << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S") << ']'
                    << '[' << std::setw(7) << logging::trivial::severity << ']'
                    << '[' << std::setw(6) << expr::attr<std::string>("Tag") << ']'
                    //<< '[' << expr::attr <boost::log::attributes::current_thread_id::value_type> ("ThreadID") << ']'
                    << '[' << std::setw(8) << a_thread_name << ']'
                    << " - " << expr::message;

    auto fileSink = logging::add_file_log(
            keywords::open_mode = std::ios_base::app,
            keywords::target = target,
            keywords::file_name = fileName
    );

    fileSink->set_formatter(formatter);
    fileSink->set_filter(logging::trivial::severity >= logging::trivial::debug);
    fileSink->locked_backend()->auto_flush();
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

void Logger::ScriptError(std::string msg)
{
    BOOST_LOG_SEV(ScriptLogger_, logging::trivial::severity_level::error) << msg.c_str();
}

void Logger::ScriptWarning(std::string msg)
{
    BOOST_LOG_SEV(ScriptLogger_, logging::trivial::severity_level::warning) << msg.c_str();
}

void Logger::ScriptInfo(std::string msg)
{
    BOOST_LOG_SEV(ScriptLogger_, logging::trivial::severity_level::info) << msg.c_str();
}

void Logger::ScriptDebug(std::string msg)
{
    BOOST_LOG_SEV(ScriptLogger_, logging::trivial::severity_level::debug) << msg.c_str();
}



