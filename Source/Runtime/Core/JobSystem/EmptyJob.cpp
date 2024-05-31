
#include "EmptyJob.h"

using namespace mikasa::Runtime::Core;

void EmptyJob::Execute()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Logger::Info("Job Finish, Message %s", Message_.c_str());
}
