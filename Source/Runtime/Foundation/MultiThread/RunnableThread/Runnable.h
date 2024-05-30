#pragma once
#include "../../Foundation.h"

namespace mikasa::Runtime::Foundation
{
    /**
     * represents the logic run on a thread.
     */
    class Runnable
    {
    public:
        virtual bool Init() = 0;
        virtual uint32 Run() = 0;
        virtual void Exit() = 0;
    };
}

