
#include "RenderScene.h"

using namespace mikasa::Runtime::Core;

void RenderScene::AddStaticMeshRenderProxy(const std::shared_ptr<StaticMeshRenderProxy>& proxy)
{
    StaticMeshRenderProxies_.push_back(proxy);
}

void RenderScene::RemoveStaticMeshRenderProxy(const std::shared_ptr<StaticMeshRenderProxy>& proxy)
{
    StaticMeshRenderProxies_.remove(proxy);
}
