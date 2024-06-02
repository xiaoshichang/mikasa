#include <format>
#include <thread>
#include <boost/lockfree/queue.hpp>
#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Foundation;

class Task
{
public:
    int Data;
};

boost::lockfree::queue<Task*> queue_(100);


void worker_thread(int i)
{
    auto workerName = std::format("worker{}", i);
    boost::log::core::get()->add_thread_attribute("ThreadName", boost::log::attributes::constant< std::string >(workerName));

    while (true)
    {
        Task* task = nullptr;
        bool got = queue_.pop(task);
        if (!got)
        {
            break;
        }
        else
        {
            Logger::Info("%s process task with data %d.", workerName.c_str(), task->Data);
            delete task;
        }
    }
    Logger::Info("%s exit.", workerName.c_str());
}

int main()
{
    Logger::Init(LogSink::ConsoleBackend, "", "");

    const int taskCount = 100;
    for(int i = 0; i < taskCount; i++)
    {
        auto task = new Task();
        task->Data = i;
        queue_.push(task);
    }

    int threadCount = 3;
    std::thread threads[3];
    for(int i = 0; i < threadCount; i++)
    {
        threads[i] = std::thread(worker_thread, i);
    }
    for(auto& t : threads)
    {
        t.join();
    }
    return 0;
}