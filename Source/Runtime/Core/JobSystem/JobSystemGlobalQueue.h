#pragma once
#include <boost/lockfree/queue.hpp>
#include "Runtime/Foundation/Foundation.h"

namespace mikasa::Runtime::Core
{
    class Job;
    class JobSystemGlobalQueue
    {
    public:
        JobSystemGlobalQueue();
        ~JobSystemGlobalQueue() = default;

    public:
        bool Enqueue(Job* job);
        Job* Dequeue();

    private:
        boost::lockfree::queue<Job*> InternalQueue_;

    };

}
