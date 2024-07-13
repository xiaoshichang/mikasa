#ifdef MIKASA_BUILDTYPE_DEBUG

#pragma once
#include <boost/python.hpp>
#include <string>
#include "Runtime/Foundation/Console/Console.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    struct StdoutRedirect
    {
        static PyObject* Write(PyObject* self, PyObject* arg)
        {
            std::size_t written(0);
            const char* msg = PyUnicode_AsUTF8(arg);
            Console::GetInstance()->OutputString(msg, ConsoleTextColor::LightGreen);
            written = strlen(msg);
            return PyLong_FromSize_t(written);
        }

        static PyObject* Flush(PyObject* args)
        {
            return Py_BuildValue("");
        }
    };


    struct StderrRedirect
    {
        static PyObject* Write(PyObject* self, PyObject* arg)
        {
            std::size_t written(0);
            const char* msg = PyUnicode_AsUTF8(arg);
            Console::GetInstance()->OutputString(msg, ConsoleTextColor::LightRed);
            written = strlen(msg);
            return PyLong_FromSize_t(written);
        }

        static PyObject* Flush(PyObject* args)
        {
            return Py_BuildValue("");
        }
    };




}

#endif


