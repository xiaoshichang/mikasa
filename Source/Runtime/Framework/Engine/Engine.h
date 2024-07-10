#pragma once

#include "Runtime/Core/Misc/ApplicationInitParam.h"
#include "Runtime/Core/Misc/WindowHandler.h"

using namespace mikasa::Runtime::Core;

namespace mikasa::Runtime::Framework
{

    /**
     * Manage all modules life cycle
     */
    class Engine
    {
    public:
        static void Init(const ApplicationInitParam& info, const WindowHandler& handler);
        static void UnInit();
        static void Update();
    };

}
