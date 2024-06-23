#pragma once
#include <memory>
#include <list>
#include "StaticMeshRenderProxy.h"

namespace mikasa::Runtime::Core
{

    class RenderScene
    {
    public:
        void AddStaticMeshRenderProxy(const std::shared_ptr<StaticMeshRenderProxy>& proxy);
        void RemoveStaticMeshRenderProxy(const std::shared_ptr<StaticMeshRenderProxy>& proxy);

    private:
        std::list<std::shared_ptr<StaticMeshRenderProxy>> StaticMeshRenderProxies_;
    };
}

