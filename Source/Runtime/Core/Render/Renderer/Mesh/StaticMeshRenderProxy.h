#pragma once

#include "RenderProxyTransformUpdateInfo.h"
#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Core/Render/RenderDevice/RenderResource/ConstantBuffer.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class StaticMesh;
    class RenderView;

    struct ConstantBufferPerObject
    {
        Matrix4x4f WorldMatrix;
    };

    struct RenderSingleViewContext
    {
        std::shared_ptr<RenderView> RenderView;
    };

    struct RenderSingleObjectContext
    {
        std::shared_ptr<ConstantBuffer<ConstantBufferPerObject>> ConstantBufferPerObject;
    };


    /**
     * represent a Renderable thing in RenderScene.
     * construct on main thread.
     * add to RenderScene on render thread.
     */
    class StaticMeshRenderProxy
    {
    public:
        explicit StaticMeshRenderProxy(RenderProxyTransform  transform, const std::shared_ptr<StaticMesh>& mesh);
        void Render(const RenderSingleViewContext& viewContext);
        void InitRHIResource();
        void UpdateTransform(const RenderProxyTransform& worldMatrix);

    private:
        std::shared_ptr<ConstantBuffer<ConstantBufferPerObject>> ConstantBufferPerObject_;
        std::shared_ptr<StaticMesh> Mesh_;
        RenderProxyTransform Transform_;

    };
}
