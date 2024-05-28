#pragma once

#include <mutex>
#include <condition_variable>
#include "Runtime/Foundation/Assert.h"

namespace mikasa::Runtime::Foundation
{

    class Semaphore
    {
    public:
        Semaphore(int initCount, int maxCount)
                : Count_(initCount)
                , MaxCount_(maxCount)
        {
            MIKASA_ASSERT(MaxCount_ >= Count_);
        }

        inline void Acquire()
        {
            // similar to lock_guard, std::unique_lock can automatically do lock and unlock during life cycle.
            // compare to lock_guard, std::unique_lock is movable so it can be a return value or param of function.
            std::unique_lock<std::mutex> lock(Protect_);

            while(Count_ <= 0)
            {
                // https://en.cppreference.com/w/cpp/thread/condition_variable/wait
                // 1. Atomically calls lock.unlock() and blocks on *this
                // 2. The thread will be unblocked when notify_all() or notify_one() is executed. It may also be unblocked spuriously.
                // 3. When unblocked, calls lock.lock() (possibly blocking on the lock), then returns.
                Signal_.wait(lock);
            }

            Count_--;
        }

        inline void Release()
        {
            /*
            https://en.cppreference.com/w/cpp/thread/condition_variable
            The thread that intends to modify the shared variable must:
                1. Acquire a std::mutex (typically via std::lock_guard).
                2. Modify the shared variable while the lock is owned.
                3. Call notify_one or notify_all on the std::condition_variable (can be done after releasing the lock).
            */
            {
                std::lock_guard<std::mutex> lock(Protect_);
                Count_++;
                if (Count_ > MaxCount_)
                {
                    throw;
                }
            }
            Signal_.notify_one();
        }

    private:
        std::mutex Protect_;
        std::condition_variable Signal_;
        int Count_;
        int MaxCount_;
    };

}