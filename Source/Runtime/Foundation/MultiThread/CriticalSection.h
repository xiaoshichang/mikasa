#pragma once

#include <mutex>

namespace mikasa::Runtime::Foundation
{
    class CriticalSection
    {
    public:
        void Enter()
        {
            Mutex_.lock();
        }

        void Exit()
        {
            Mutex_.unlock();
        }

    private:
        std::mutex Mutex_;
    };
}