#pragma once

#include <mutex>
#include <condition_variable>
#include "Runtime/Foundation/Assert.h"

namespace mikasa::Runtime::Foundation
{
    class AutoResetEvent
    {
    public:
        explicit AutoResetEvent(bool initial = false) : Flag_(initial)
        {
        }

        inline void Set()
        {
            std::lock_guard<std::mutex> _(Protect_);
            Flag_ = true;
            Signal_.notify_one();
        }

        inline void Reset()
        {
            std::lock_guard<std::mutex> _(Protect_);
            Flag_ = false;
        }

        inline void WaitOne()
        {
            std::unique_lock<std::mutex> lk(Protect_);
            while( !Flag_ )
            {
                Signal_.wait(lk);
            }
            Flag_ = false; // waiting resets the flag
        }

    private:
        bool Flag_;
        std::mutex Protect_;
        std::condition_variable Signal_;
    };
}