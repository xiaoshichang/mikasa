#pragma once
#include <memory>
#include <list>
#include "StaticMeshRenderProxy.h"
#include "Light/LightRenderProxy.h"

namespace mikasa::Runtime::Core
{

    class RenderScene
    {
    public:
        void AddStaticMeshRenderProxy(const std::shared_ptr<StaticMeshRenderProxy>& proxy);
        void RemoveStaticMeshRenderProxy(const std::shared_ptr<StaticMeshRenderProxy>& proxy);
        void AddLightRenderProxy(const std::shared_ptr<LightRenderProxy>& proxy);
        void RemoveLightRenderProxy(const std::shared_ptr<LightRenderProxy>& proxy);

    private:
        std::list<std::shared_ptr<StaticMeshRenderProxy>> StaticMeshRenderProxies_;
        std::list<std::shared_ptr<LightRenderProxy>> LightRenderProxies_;

    };
}

