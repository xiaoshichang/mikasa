
#include "RenderThreadRunnable.h"

using namespace mikasa::Runtime::Module;

bool RenderThreadRunnable::Init()
{
    boost::log::core::get()->add_thread_attribute("ThreadName", boost::log::attributes::constant< std::string >("Render"));
    Logger::Info("RenderThread Init.");
    return true;
}

uint32 RenderThreadRunnable::Run()
{
    for (int i = 0; i < 3; ++i)
    {
        Logger::Info("RenderThread Run.");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}

void RenderThreadRunnable::Exit()
{
    Logger::Info("RenderThread Exit.");
}

void RenderThreadRunnable::Stop()
{
    Logger::Info("RenderThread Stop.");
}
