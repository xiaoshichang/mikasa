#pragma once
#include <string>

namespace mikasa::Runtime::Core
{
    class ScriptVM
    {
    public:
        ScriptVM() = default;
        virtual ~ScriptVM() = default;

    public:
        virtual void EvaluateString(const std::string& input) = 0;
    };
}

