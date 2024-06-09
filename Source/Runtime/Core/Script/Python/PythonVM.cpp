
#include "PythonVM.h"
#include "Runtime/Foundation/Console/Console.h"
#include <boost/filesystem.hpp>

#include "Runtime/ScriptExport/Python/MLogger.h"
#include "Runtime/ScriptExport/Python/IORedirect.h"

using namespace mikasa::Runtime::Core;




PythonVM::PythonVM()
{
    SetupPythonHome();
    SetupBuildEngineModules();
    Py_Initialize();
    RedirectIO();
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

void PythonVM::SetupBuildEngineModules()
{
    PyImport_AppendInittab("MLogger", PyInit_MLogger);
#ifdef MIKASA_BUILDTYPE_DEBUG
    PyImport_AppendInittab("IORedirect", PyInit_IORedirect);
#endif
}



void PythonVM::RedirectIO()
{
    const char* code =
R"(
import sys
import IORedirect
sys.stdout = IORedirect.StdoutRedirect()
sys.stderr = IORedirect.StderrRedirect()
)";
    PyRun_SimpleString(code);
}

