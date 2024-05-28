#pragma once
#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Core/Misc/ApplicationInitParam.h"

using namespace mikasa::Runtime::Core;

namespace mikasa::Runtime::Module
{
    class MemoryManagementModule
    {
    public:
        static void Init(const ApplicationInitParam& info);
        static void UnInit();
    };
}


