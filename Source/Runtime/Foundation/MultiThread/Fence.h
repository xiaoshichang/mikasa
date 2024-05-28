#pragma once

#include "Semaphore.h"

namespace mikasa::Runtime::Foundation
{

    class Fence
    {
    public:
        Fence() : m_Semaphore(0, 1)
        {}

    public:
        inline void Wait()
        {
            m_Semaphore.Acquire();
        }

        inline void Signal()
        {
            m_Semaphore.Release();
        }

    private:
        Semaphore m_Semaphore;
    };

}