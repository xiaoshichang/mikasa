#pragma once
#include "Runtime/Core/Misc/ApplicationInitParam.h"
#include "Runtime/Core/Misc/WindowHandler.h"


namespace mikasa::Runtime::Core
{
    class RHI
    {
    public:
        RHI() = default;
        virtual ~RHI() = default;
        virtual void InitRHI(const ApplicationInitParam& param, const WindowHandler& windowHandler) = 0;
        virtual void UnInitRHI() = 0;

    };
}


