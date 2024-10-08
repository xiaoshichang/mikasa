
#include "Engine.h"


#include "Runtime/Module/SystemInfoModule/SystemInfoModule.h"
#include "Runtime/Module/MemoryManagementModule/MemoryManagementModule.h"
#include "Runtime/Module/RenderModule/RenderModule.h"
#include "Runtime/Module/JobSystemModule/JobSystemModule.h"
#include "Runtime/Module/ScriptModule/ScriptModule.h"
#include "Runtime/Module/SceneModule/SceneModule.h"
#include "../GameViewClient/GameViewClient.h"

using namespace mikasa::Runtime::Framework;
using namespace mikasa::Runtime::Module;
using namespace mikasa::Runtime::Foundation;

void Engine::Init(const ApplicationInitParam& info, const WindowHandler& handler)
{
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
    RenderModule::Init(info, handler);
    SceneModule::Init();
    GameViewClient::Init();
}

void Engine::UnInit()
{
    GameViewClient::UnInit();
    SceneModule::UnInit();
    RenderModule::UnInit();
    JobSystemModule::UnInit();
    ScriptModule::UnInit();
    MemoryManagementModule::UnInit();
    SystemInfoModule::Uninit();
    Logger::UnInit();

}

void Engine::Update()
{
    SceneModule::Update();
}
