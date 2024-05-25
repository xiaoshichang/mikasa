#pragma once
#include "Runtime/Core/Misc/ApplicationInitParam.h"

using namespace mikasa::Runtime::Core;

namespace mikasa
{
    namespace Runtime
    {
        namespace Module
        {
            class LogModule
            {
            public:
                static void Init(const ApplicationInitParam& info);
                static void Tick();
                static void UnInit();
            };
        }
    }
}


