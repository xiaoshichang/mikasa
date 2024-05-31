
#include <thread>
#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Foundation/MultiThread.h"

using namespace mikasa::Runtime::Foundation;


AutoResetEvent e;
bool quit = false;
int count = 5;

void worker_thread()
{
    for(int i = 0; i < count; ++i)
    {
        if (i == count - 1)
        {
            quit = true;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        Logger::Info("worker thread set event. %d", i);
        e.Set();
    }
}

int main()
{
    Logger::Init(LogSink::Console, "", "");
    std::thread t1(worker_thread);

    while (!quit)
    {
        e.Wait();
        Logger::Info("main thread get event.");
    }

    t1.join();
    return 0;
}