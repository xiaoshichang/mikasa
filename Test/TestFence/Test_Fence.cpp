
#include <iostream>
#include <thread>
#include <chrono>
#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Foundation/MultiThread.h"

using namespace mikasa::Runtime::Foundation;

Fence f1;
Fence f2;

void worker_thread()
{
    f1.Wait();
    Logger::Info("after f1 wait");
    Logger::Info("before f2 signal");
    f2.Signal();
}

int main()
{
    Logger::Init(LogSink::Console, "", "");

    std::thread worker1(worker_thread);
    Logger::Info("before f1 signal");
    f1.Signal();
    f2.Wait();
    Logger::Info("after f2 wait");

    worker1.join();
    Logger::Info("after join");
    return 0;
}