#pragma once

#include <string>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/log/core.hpp>
#include <boost/log/core/record.hpp>
#include "boost/log/trivial.hpp"

#include <boost/log/expressions.hpp>
#include <boost/log/sinks/unlocked_frontend.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>

#include "../Console/Console.h"


namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", logging::trivial::severity_level)

namespace mikasa::Runtime::Foundation
{
    class ConsoleSink : public sinks::basic_formatted_sink_backend<char, sinks::combine_requirements<sinks::concurrent_feeding, sinks::formatted_records>::type>
    {
    public:
        void consume(logging::record_view const& rec, string_type const& formattedRecord)
        {
            logging::value_ref< logging::trivial::severity_level, tag::severity > level = rec[severity];
            auto color = ConsoleTextColor::White;
            switch (level.get())
            {
                case logging::trivial::severity_level::debug:
                case logging::trivial::severity_level::trace:
                    color = ConsoleTextColor::LightGreen;
                    break;
                case logging::trivial::severity_level::info:
                    break;
                case logging::trivial::severity_level::warning:
                    color = ConsoleTextColor::Yellow;
                    break;
                case logging::trivial::severity_level::error:
                case logging::trivial::severity_level::fatal:
                    color = ConsoleTextColor::LightRed;
                    break;
            }
            auto formattedRecordNewline = formattedRecord + "\n";
            Console::OnOutputString(formattedRecordNewline, color);
            //std::cout << formattedRecord << std::endl;
        }
    };

}
