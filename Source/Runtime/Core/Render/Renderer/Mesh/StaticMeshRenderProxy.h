#pragma once

#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Core/Render/Renderer/Renderer.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class StaticMesh;

    struct ConstantBufferPerObject
    {
        Matrix4x4f WorldMatrix;
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
        explicit StaticMeshRenderProxy(const Matrix4x4f& worldMatrix, const std::shared_ptr<StaticMesh>& mesh);
        void Render(const RenderSingleViewContext& viewContext);
        void InitRHIResource();

    private:
        ConstantBufferPerObject ConstantBufferPerObjectData_;
        std::shared_ptr<ConstantBuffer<ConstantBufferPerObject>> ConstantBufferPerObject_;
        std::shared_ptr<StaticMesh> Mesh_;

    };
}
