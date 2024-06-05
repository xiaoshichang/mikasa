#include <boost/python.hpp>
#include <cstdlib>


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
    PyImport_AppendInittab("FooModule", PyInit_FooModule);
    Py_Initialize();
    PyRun_SimpleString("print(\"hello world.\")");
    PyRun_SimpleString("import FooModule");
    PyRun_SimpleString("a = FooModule.greet()");
    PyRun_SimpleString("print(a)");
    Py_Finalize();

    return 0;
}