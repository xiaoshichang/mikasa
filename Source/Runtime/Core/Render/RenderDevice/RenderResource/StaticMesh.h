#pragma once

#include "RenderResource.h"
#include "VertexStreamCmpt.h"
#include "../RHI/RHIBoundShaderState.h"
#include "Runtime/Core/Render/Renderer/Renderer.h"
#include "Runtime/Core/Render/Renderer/Mesh/StaticMeshRenderProxy.h"
#include <memory>

namespace mikasa::Runtime::Core
{
    class RHIVertexBuffer;
    class RHIIndexBuffer;

    class StaticMesh : public RenderResource, public std::enable_shared_from_this<StaticMesh>
    {
    public:
        explicit StaticMesh(const std::string& asset);
        ~StaticMesh() override;

        void InitRHIResource() override;
        void Render(const RenderSingleViewContext& viewContext, const RenderSingleObjectContext& objectContext);

    private:

        std::shared_ptr<VertexStreamCmpt> PositionCmpt_;
        std::shared_ptr<VertexStreamCmpt> NormalCmpt_;
        std::shared_ptr<VertexStreamCmpt> ColorCmpt_;
        std::shared_ptr<RHIIndexBuffer> IndexBuffer_;
        std::shared_ptr<RHIVertexShader> VertexShader_;
        std::shared_ptr<RHIPixelShader> PixelShader_;
        std::shared_ptr<RHIBoundShaderState> ShaderState_;





    };
}
