#pragma once

#include "Runtime/Core/Misc/ApplicationInitParam.h"
#include "Runtime/Core/Script/ScriptVM.h"


using namespace mikasa::Runtime::Core;

namespace mikasa::Runtime::Module
{
    class ScriptModule
    {
    public:
        static void Init(const ApplicationInitParam& info);
        static void UnInit();
        static void DoString(const std::string& s);

#if MIKASA_BUILDTYPE_DEBUG
        static void ConsumeConsoleInput();
#endif


    private:
        static ScriptVM* VM_;
    };
}


