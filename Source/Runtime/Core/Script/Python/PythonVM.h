#pragma once
#include <boost/python.hpp>
#include "../ScriptVM.h"

namespace mikasa::Runtime::Core
{
    class PythonVM : public ScriptVM
    {
    public:
        PythonVM();
        ~PythonVM() override = default;

        void EvaluateString(const std::string &input) override;

    private:
        /**
         * setup python home path so python can be initialized successfully.
         */
        static void SetupPythonHome();


    };

}

