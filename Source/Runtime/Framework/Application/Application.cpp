#include <format>
#include "Application.h"
#include "Runtime/Framework/MainWindow/MainWindow.h"
#include "Runtime/Framework/GameViewClient/GameViewClient.h"
#include "Runtime/Framework/Engine/Engine.h"
#include "Runtime/Foundation/Console/Console.h"
#include "Runtime/Core/Render/Sync/RenderThreadFrameSync.h"
#include "Runtime/Module/ScriptModule/ScriptModule.h"
#include "Runtime/Module/SceneModule/SceneModule.h"


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
    Engine::Init(info, MainWindow::GetWindowHandler());

}

void Application::Run()
{
    while (!IsApplicationQuit_)
    {
        StartFrame();

        PreUpdate();
        Update();
        PostUpdate();

        Render();
        AfterRender();

        EndFrame();
    }
}

void Application::UnInit()
{
    Engine::UnInit();
    MainWindow::UnInit();
#if MIKASA_BUILDTYPE_DEBUG
    Console::UnInit();
#endif
}

void Application::RequestQuit()
{
    IsApplicationQuit_ = true;
}

void Application::StartFrame()
{
    DispatchOSMessage();
}

void Application::PreUpdate()
{

}

void Application::Update()
{

#if MIKASA_BUILDTYPE_DEBUG
    ScriptModule::ConsumeConsoleInput();
#endif
    Engine::Update();
}

void Application::PostUpdate()
{
}

void Application::Render()
{
    GameViewClient::Render();
    auto lambda = []()
    {
        RenderDevice::RHI->Present();
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}

void Application::AfterRender()
{

}

void Application::EndFrame()
{
    RenderThreadFrameSync::Sync();
}
