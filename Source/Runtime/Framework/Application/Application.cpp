#include <format>
#include "Application.h"
#include "Runtime/Module/SystemInfoModule/SystemInfoModule.h"
#include "Runtime/Module/MemoryManagementModule/MemoryManagementModule.h"
#include "Runtime/Module/RenderModule/RenderModule.h"
#include "Runtime/Module/JobSystemModule/JobSystemModule.h"
#include "Runtime/Framework/MainWindow/MainWindow.h"



using namespace mikasa::Runtime::Framework;
using namespace mikasa::Runtime::Module;


void Application::Init(const ApplicationInitParam& info)
{
    Logger::Init(LogSink::Console|LogSink::File, info.LogDir, info.LogPath);
    SystemInfoModule::Init(info);
    SystemInfoModule::OutputInfo();
    MemoryManagementModule::Init(info);
    MainWindow::Init(this, info);
    JobSystemModule::Init(info);
    RenderModule::Init(info);

}

void Application::Run()
{
    while (!IsApplicationQuit_)
    {
        DispatchOSMessage();
    }
}

void Application::UnInit()
{
    RenderModule::UnInit();
    JobSystemModule::UnInit();
    MainWindow::UnInit();
    MemoryManagementModule::UnInit();
    SystemInfoModule::Uninit();
    Logger::UnInit();
}

void Application::RequestQuit()
{
    IsApplicationQuit_ = true;
}
