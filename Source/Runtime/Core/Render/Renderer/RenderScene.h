#pragma once
#include "Runtime/Core/Render/Renderer/Mesh/StaticMeshRenderProxy.h"
#include "Runtime/Core/Scene/Component/StaticMeshRenderCmpt.h"
#include <memory>
#include <list>
#include <vector>

namespace mikasa::Runtime::Core
{

    class LightRenderProxy;
    class RenderTarget;

    /**
     * "scene" on render thread.
     * all function should be call on render thread.
     */
    class RenderScene
    {
    public:
        RenderScene();
        ~RenderScene();

    private:
        void InitRenderResource();
        void UnInitRenderResource();

    public:
        void AddStaticMeshRenderProxy(const std::shared_ptr<StaticMeshRenderProxy>& proxy);
        void RemoveStaticMeshRenderProxy(const std::shared_ptr<StaticMeshRenderProxy>& proxy);
        void AddLightRenderProxy(const std::shared_ptr<LightRenderProxy>& proxy);
        void RemoveLightRenderProxy(const std::shared_ptr<LightRenderProxy>& proxy);
        void AddRenderProxyTransformUpdateInfo(const RenderProxyTransformUpdateInfo& info);
        void ProcessUpdatedTransform();

    public:
        std::list<std::shared_ptr<StaticMeshRenderProxy>>& GetAllStaticMeshRenderProxies();

    private:
        std::list<std::shared_ptr<StaticMeshRenderProxy>> StaticMeshRenderProxies_;
        std::vector<RenderProxyTransformUpdateInfo> RenderProxiesTransformUpdate_{};

        std::list<std::shared_ptr<LightRenderProxy>> LightRenderProxies_;


    };
}

