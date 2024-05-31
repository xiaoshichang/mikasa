
#include "JobSystemModule.h"

using namespace mikasa::Runtime::Module;

JobSystem* JobSystemModule::JobSystem_ = nullptr;

void JobSystemModule::Init(const ApplicationInitParam& param)
{
    Logger::Info("JobSystemModule Init ok.");
    JobSystemInitParam jobSystemInitParam{};
    jobSystemInitParam.WorkerThreadCount = 4;

    JobSystem_ = new JobSystem(jobSystemInitParam);
}

void JobSystemModule::UnInit()
{
    MIKASA_ASSERT(JobSystem_ != nullptr);
    delete JobSystem_;
    JobSystem_ = nullptr;
    Logger::Info("JobSystemModule UnInit ok.");
}

uint32 JobSystemModule::CalculateWorkerNumBaseSystemInfo()
{
    return 4;
}
