
#include <iostream>
#include <thread>
#include <chrono>
#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Foundation/MultiThread.h"

using namespace mikasa::Runtime::Foundation;

const int LOOP_COUNT = 100000;

CriticalSection cs;
int counter = 0;

void worker_thread()
{
    for (int i = 0; i < LOOP_COUNT; ++i)
    {
        cs.Enter();
        counter += 1;
        cs.Exit();
    }
}

int main()
{
    Logger::Init(LogSink::Console, "", "");
    std::thread t1(worker_thread);
    std::thread t2(worker_thread);
    t1.join();
    t2.join();

    if (counter == LOOP_COUNT * 2)
    {
        return 0;
    }
    return 1;
}