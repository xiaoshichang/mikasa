
#include "RenderScene.h"
#include "../RenderDevice/RenderResource/RenderTarget.h"
#include "Runtime/Framework/Application/Application.h"
#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"
#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Framework;
using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

RenderScene::RenderScene()
{
    InitRenderResource();
}

RenderScene::~RenderScene()
{
    UnInitRenderResource();
}

/**
 * run on main thread
 */
void RenderScene::InitRenderResource()
{
    RenderTextureDesc desc{};
    desc.Format = PixelFormat::PF_R8G8B8A8_UNorm;

    if (Application::Param.EditorMode)
    {
        desc.Width = 1024;
        desc.Height = 768;
    }
    else
    {
        desc.Width = Application::Param.WindowWidth;
        desc.Height = Application::Param.WindowHeight;
    }
    desc.Flag |= RHITextureCreateFlag::TCF_AsRenderTarget;

    SceneColorRT = std::make_shared<RenderTarget>(desc);
    auto lambda = [=, this] ()
    {
        SceneColorRT->InitRHIResource();
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);

}

/**
 * run on main thread
 */
void RenderScene::UnInitRenderResource()
{
    SceneColorRT.reset();
}

void RenderScene::AddStaticMeshRenderProxy(const std::shared_ptr<StaticMeshRenderProxy>& proxy)
{
    StaticMeshRenderProxies_.push_back(proxy);
    Logger::Info("AddStaticMeshRenderProxy");
}

void RenderScene::RemoveStaticMeshRenderProxy(const std::shared_ptr<StaticMeshRenderProxy>& proxy)
{
    StaticMeshRenderProxies_.remove(proxy);
    Logger::Info("RemoveStaticMeshRenderProxy");
}

void RenderScene::AddLightRenderProxy(const std::shared_ptr<LightRenderProxy> &proxy)
{
    LightRenderProxies_.push_back(proxy);
    Logger::Info("AddLightRenderProxy");
}

void RenderScene::RemoveLightRenderProxy(const std::shared_ptr<LightRenderProxy> &proxy)
{
    LightRenderProxies_.remove(proxy);
    Logger::Info("RemoveLightRenderProxy");
}

std::list<std::shared_ptr<StaticMeshRenderProxy>>& RenderScene::GetAllStaticMeshRenderProxies()
{
    return StaticMeshRenderProxies_;
}

std::shared_ptr<RenderTarget> &RenderScene::GetSceneColorRT()
{
    return SceneColorRT;
}








