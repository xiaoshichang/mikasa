#pragma once

#include <boost/python.hpp>
#include "Runtime/Foundation/Log/Logger.h"

using namespace mikasa::Runtime::Foundation;


BOOST_PYTHON_MODULE(MLogger)
{
    using namespace boost::python;
    def("Info", Logger::ScriptInfo);
    def("Warning", Logger::ScriptWarning);
    def("Error", Logger::ScriptError);
    def("Debug", Logger::ScriptDebug);
}
