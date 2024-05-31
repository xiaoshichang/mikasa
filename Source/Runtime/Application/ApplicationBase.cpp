#include <format>
#include "ApplicationBase.h"
#include "Runtime/Module/SystemInfoModule/SystemInfoModule.h"
#include "Runtime/Module/MemoryManagementModule/MemoryManagementModule.h"
#include "Runtime/Module/RenderModule/RenderModule.h"
#include "Runtime/Module/JobSystemModule/JobSystemModule.h"

#include "Runtime/Core/JobSystem/EmptyJob.h"

using namespace mikasa::Runtime::Application;
using namespace mikasa::Runtime::Module;


void ApplicationBase::Init(const ApplicationInitParam& info)
{
    Logger::Init(LogSink::Console|LogSink::File, info.LogDir, info.LogPath);
    SystemInfoModule::Init(info);
    SystemInfoModule::OutputInfo();
    MemoryManagementModule::Init(info);
    JobSystemModule::Init(info);
    RenderModule::Init(info);

}

void ApplicationBase::Run()
{
    std::vector<Job*> jobs;
    while (!IsApplicationQuit_)
    {
        for(int i = 0; i < 20; i++)
        {
            auto job = new EmptyJob(std::format("{}-th", i));
            jobs.push_back(job);
            job->Schedule();
        }

        for (auto job : jobs)
        {
            job->WaitCompletion();
        }

        IsApplicationQuit_ = true;
    }
}

void ApplicationBase::UnInit()
{
    RenderModule::UnInit();
    JobSystemModule::UnInit();
    MemoryManagementModule::UnInit();
    SystemInfoModule::Uninit();
    Logger::UnInit();
}

void ApplicationBase::TryQuit()
{
    IsApplicationQuit_ = true;
}
