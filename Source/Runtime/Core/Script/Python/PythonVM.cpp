
#include "PythonVM.h"
#include "Runtime/Foundation/Console/Console.h"
#include <boost/filesystem.hpp>

using namespace mikasa::Runtime::Core;

PythonVM::PythonVM()
{
    SetupPythonHome();
    Py_Initialize();
}

void PythonVM::EvaluateString(const std::string &input)
{
    PyRun_SimpleString(input.c_str());
}

void PythonVM::SetupPythonHome()
{
    boost::filesystem::path full_path(boost::filesystem::current_path());
    boost::filesystem::path python_home = full_path / ".." / ".." / ".." / "ThirdPartySource" / "python" / "Python-3.12.3";
    std::string ev = "PYTHONHOME=" + python_home.string();
    _putenv(ev.c_str());
}

