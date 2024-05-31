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

        /**
        * Sets the state of the event to signaled, allowing one or more waiting threads to proceed.
        */
        inline void Set()
        {
            std::lock_guard<std::mutex> _(Protect_);
            Flag_ = true;
            Signal_.notify_all();
        }

        inline void Reset()
        {
            std::lock_guard<std::mutex> _(Protect_);
            Flag_ = false;
        }

        inline void Wait()
        {
            std::unique_lock<std::mutex> lk(Protect_);
            Signal_.wait(lk, [=] { return Flag_;});
            Flag_ = false;
        }

        inline void WaitFor(std::chrono::milliseconds duration)
        {
            std::unique_lock<std::mutex> lk(Protect_);
            Signal_.wait_for(lk, duration, [=] { return Flag_;});
            Flag_ = false;
        }

    private:
        bool Flag_;
        std::mutex Protect_;
        std::condition_variable Signal_;
    };
}