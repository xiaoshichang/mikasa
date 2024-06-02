
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Foundation/MultiThread.h"

using namespace mikasa::Runtime::Foundation;

Semaphore s(0, 2);


void worker_thread(int i)
{
    Logger::Info("before worker[%d][%d] Acquire ", i, std::this_thread::get_id());
    s.Acquire();
    Logger::Info("after worker[%d][%d] Acquire ", i, std::this_thread::get_id());
}

int main()
{
    Logger::Init(LogSink::ConsoleBackend, "", "");

    int threadCount = 5;
    std::thread threads[5];
    for(int i = 0; i < threadCount; i++)
    {
        threads[i] = std::thread(worker_thread, i);
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    for(int i = 0; i < threadCount; i++)
    {
        s.Release();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    for(auto& t : threads)
    {
        t.join();
    }
    Logger::Info("all finish.");
    return 0;
}