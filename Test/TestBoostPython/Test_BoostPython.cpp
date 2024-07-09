#include <boost/python.hpp>
#include <boost/filesystem.hpp>
#include <cstdlib>
#include <iostream>


namespace bp = boost::python;

char const* greet()
{
    return "greeting....";
}

BOOST_PYTHON_MODULE(FooModule)
{
    using namespace boost::python;
    def("greet", greet);
}


int main()
{
    boost::filesystem::path full_path(boost::filesystem::current_path());
    boost::filesystem::path python_home = full_path / ".." / ".." / ".." / "ThirdPartySource" / "python" / "Python-3.12.4";
    std::string ev = "PYTHONHOME=" + python_home.string();
    _putenv(ev.c_str());

    PyImport_AppendInittab("FooModule", PyInit_FooModule);
    Py_Initialize();
    PyRun_SimpleString("print(\"hello world.\")");
    PyRun_SimpleString("import FooModule");
    PyRun_SimpleString("a = FooModule.greet()");
    PyRun_SimpleString("print(a)");
    Py_Finalize();

    return 0;
}