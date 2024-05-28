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
                : m_Count(initCount)
                , m_MaxCount(maxCount)
        {
            MIKASA_ASSERT(m_MaxCount >= m_Count);
        }

        inline void Acquire()
        {
            std::unique_lock<std::mutex> lock(m_MTX);

            /*
            https://en.cppreference.com/w/cpp/thread/condition_variable/wait
            Atomically releases lock, blocks the current executing thread, and adds it to the list of threads waiting on *this.
            The thread will be unblocked when notify_all() or notify_one() is executed. It may also be unblocked spuriously.
            When unblocked, regardless of the reason, lock is reacquired and wait exits.
            If this function exits via exception, lock is also reacquired. (until C++14)

            wait会自动释放锁，阻塞当前线程，然后把自己加入条件变量的waiting列表。
            当其他线程调用notify_all或者notify_one时，当前线程会被唤醒。或者虚假唤醒。
            当被唤醒时，不管什么理由，会再次请求锁，然后退出wait调用。
            即使通过异常退出wait调用，也会再次请求锁。

            基于这样的保证，m_Count > 0 的判断和 m_Count-- 的修改都受到互斥量的保护。
            */
            m_CV.wait(lock, [=] { return m_Count > 0; });

            m_Count--;
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
                std::lock_guard<std::mutex> lock(m_MTX);
                m_Count++;
                if (m_Count > m_MaxCount)
                {
                    throw;
                }
            }
            m_CV.notify_one();
        }

    private:
        std::mutex m_MTX;
        std::condition_variable m_CV;
        int m_Count;
        int m_MaxCount;
    };

}