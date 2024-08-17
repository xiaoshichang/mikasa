
#include "WindowsPlayer.h"
#include "Runtime/Framework/GameViewClient/GameViewClient.h"
#include "Runtime/Module/SceneModule/SceneModule.h"

using namespace mikasa::Player;
using namespace mikasa::Runtime::Module;

void WindowsPlayer::Init(const ApplicationInitParam &info)
{
    WindowsApplication::Init(info);
    SceneModule::SyncLoadScene("");
}

void WindowsPlayer::Render()
{
    GameViewClient::Render();
    auto lambda = [=]()
    {
        auto dst = RenderDevice::RHI->GetBackBufferRT();
        auto src = GameViewClient::GetSceneColorRT()->GetRHITexture().get();
        RenderDevice::RHI->CopyResource(dst, src);
        RenderDevice::RHI->Present();
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}
