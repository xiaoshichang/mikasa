
#include "PythonVM.h"
#include "Runtime/Foundation/Foundation.h"
#include "Runtime/ScriptExport/Python/MLogger.h"
#include "Runtime/ScriptExport/Python/IORedirect.h"
#include "Runtime/ScriptExport/Python/MScene.h"

#include <boost/filesystem.hpp>

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

PythonVM::PythonVM()
{
    SetupPythonHome();
    SetupBuildEngineModules();
    Py_Initialize();
    Logger::Debug("PythonVM Py_Initialize Ok.");

#ifdef MIKASA_BUILDTYPE_DEBUG
    RedirectIO();
#endif
}

void PythonVM::EvaluateString(const std::string &input)
{
    PyObject *m, *d, *v;
    m = PyImport_AddModule("__main__");
    if (m == nullptr)
    {
        throw;
    }
    d = PyModule_GetDict(m);
    v = PyRun_StringFlags(input.c_str(), Py_single_input, d, d, nullptr);
    if (v == nullptr)
    {
        PyErr_Print();
        return;
    }
    Py_DECREF(v);
}

void PythonVM::SetupPythonHome()
{
    const char* mikasaPythonRootName = "MIKASA_PYTHON_HOME";
    if (const char* mikasa_python_root = getenv(mikasaPythonRootName))
    {
        std::string ev = std::string("PYTHONHOME=") + std::string(mikasa_python_root);
        _putenv(ev.c_str());
    }
    else
    {
        Logger::Error("env variable MIKASA_PYTHON_HOME should be set.");
        MIKASA_ASSERT(false);
    }
}

void PythonVM::SetupBuildEngineModules()
{
    PyImport_AppendInittab("MLogger", PyInit_MLogger);
    PyImport_AppendInittab("MScene", PyInit_MScene);
#ifdef MIKASA_BUILDTYPE_DEBUG
    PyImport_AppendInittab("IORedirect", PyInit_IORedirect);
#endif
}


#ifdef MIKASA_BUILDTYPE_DEBUG
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
#endif

