#include <boost/python.hpp>
#include "Runtime/Core/Script/Python/PythonIORedirect.h"

using namespace mikasa::Runtime::Core;

BOOST_PYTHON_MODULE(IORedirect)
{
    using namespace boost::python;
    class_<StdoutRedirect>("StdoutRedirect")
        .def("write", &StdoutRedirect::Write)
        .def("flush", &StdoutRedirect::Flush)
        ;

    class_<StderrRedirect>("StderrRedirect")
        .def("write", &StderrRedirect::Write)
        .def("flush", &StderrRedirect::Flush)
        ;
}
