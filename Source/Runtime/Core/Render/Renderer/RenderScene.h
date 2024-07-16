#pragma once
#include <memory>
#include <list>

namespace mikasa::Runtime::Core
{

    class StaticMeshRenderProxy;
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
        std::shared_ptr<RenderTarget>& GetSceneColorRT();

        void AddStaticMeshRenderProxy(const std::shared_ptr<StaticMeshRenderProxy>& proxy);
        void RemoveStaticMeshRenderProxy(const std::shared_ptr<StaticMeshRenderProxy>& proxy);
        void AddLightRenderProxy(const std::shared_ptr<LightRenderProxy>& proxy);
        void RemoveLightRenderProxy(const std::shared_ptr<LightRenderProxy>& proxy);

    public:
        std::list<std::shared_ptr<StaticMeshRenderProxy>>& GetAllStaticMeshRenderProxies();

    private:
        std::list<std::shared_ptr<StaticMeshRenderProxy>> StaticMeshRenderProxies_;
        std::list<std::shared_ptr<LightRenderProxy>> LightRenderProxies_;

        std::shared_ptr<RenderTarget> SceneColorRT;

    };
}

