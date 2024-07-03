
#include "RenderScene.h"
#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

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
