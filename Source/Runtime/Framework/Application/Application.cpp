#include <format>
#include "Application.h"
#include "Runtime/Framework/MainWindow/MainWindow.h"
#include "Runtime/Foundation/Console/Console.h"

#include "Runtime/Module/SystemInfoModule/SystemInfoModule.h"
#include "Runtime/Module/MemoryManagementModule/MemoryManagementModule.h"
#include "Runtime/Module/RenderModule/RenderModule.h"
#include "Runtime/Module/JobSystemModule/JobSystemModule.h"
#include "Runtime/Module/ScriptModule/ScriptModule.h"
#include "Runtime/Module/SceneModule/SceneModule.h"
#include "Runtime/Core/Render/Sync/RenderThreadFrameSync.h"


using namespace mikasa::Runtime::Framework;
using namespace mikasa::Runtime::Module;
using namespace mikasa::Runtime::Foundation;

ApplicationInitParam Application::Param;

void Application::Init(const ApplicationInitParam& info)
{

#if MIKASA_BUILDTYPE_DEBUG
    Console::Init();
#endif

    MainWindow::Init(this, info);

#if MIKASA_BUILDTYPE_DEBUG
    Logger::Init(LogSink::ConsoleBackend | LogSink::FileBackend, info.LogDir, info.LogPath);
#else
    Logger::Init(LogSink::FileBackend, info.LogDir, info.LogPath);
#endif

    SystemInfoModule::Init(info);
    SystemInfoModule::OutputInfo();
    MemoryManagementModule::Init(info);
    ScriptModule::Init(info);
    JobSystemModule::Init(info);

    auto windowHandler = MainWindow::GetWindowHandler();
    RenderModule::Init(info, windowHandler);

    SceneModule::Init();
    SceneModule::SyncLoadScene("");
}

void Application::Run()
{
    while (!IsApplicationQuit_)
    {
        DispatchOSMessage();
#if MIKASA_BUILDTYPE_DEBUG
        ScriptModule::ConsumeConsoleInput();
#endif
        SceneModule::Update();
        SceneModule::Render();

        RenderThreadFrameSync::Sync();
    }
}

void Application::UnInit()
{
    SceneModule::UnInit();
    RenderModule::UnInit();
    JobSystemModule::UnInit();
    ScriptModule::UnInit();
    MemoryManagementModule::UnInit();
    SystemInfoModule::Uninit();
    Logger::UnInit();

    MainWindow::UnInit();
#if MIKASA_BUILDTYPE_DEBUG
    Console::UnInit();
#endif
}

void Application::RequestQuit()
{
    IsApplicationQuit_ = true;
}
