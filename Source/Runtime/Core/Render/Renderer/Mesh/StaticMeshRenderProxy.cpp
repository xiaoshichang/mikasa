
#include "StaticMeshRenderProxy.h"
#include "../../RenderDevice/RenderResource/StaticMesh.h"

using namespace mikasa::Runtime::Core;

StaticMeshRenderProxy::StaticMeshRenderProxy(const Matrix4x4f &worldMatrix, const std::shared_ptr<StaticMesh>& mesh)
    : Mesh_(mesh)
{
    ConstantBufferPerObjectData_.WorldMatrix = worldMatrix;

    auto lambda = [this]()
    {
        InitRHIResource();
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}


void StaticMeshRenderProxy::Render(const RenderSingleViewContext& viewContext)
{
    RenderSingleObjectContext objectContext;
    objectContext.ConstantBufferPerObject = ConstantBufferPerObject_;

    Mesh_->Render(viewContext, objectContext);
}

void StaticMeshRenderProxy::InitRHIResource()
{
    ConstantBufferPerObject_ = std::make_shared<ConstantBuffer<ConstantBufferPerObject>>(ConstantBufferPerObjectData_);
}
