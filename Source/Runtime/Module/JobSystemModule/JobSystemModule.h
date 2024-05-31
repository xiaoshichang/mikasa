#pragma once

#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Foundation/MultiThread.h"
#include "Runtime/Core/Misc/ApplicationInitParam.h"
#include "Runtime/Core/JobSystem/JobSystem.h"


using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Module
{

    class JobSystemModule
    {
    public:
        static void Init(const ApplicationInitParam& param);
        static void UnInit();

    private:
        static uint32 CalculateWorkerNumBaseSystemInfo();

    private:
        static JobSystem* JobSystem_;
    };


}
