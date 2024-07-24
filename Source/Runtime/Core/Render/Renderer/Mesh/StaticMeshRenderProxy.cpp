
#include "StaticMeshRenderProxy.h"

#include <utility>
#include "../../RenderDevice/RenderResource/StaticMesh.h"

using namespace mikasa::Runtime::Core;

StaticMeshRenderProxy::StaticMeshRenderProxy(Transform transform, const std::shared_ptr<StaticMesh>& mesh)
    : Mesh_(mesh)
    , Transform_(std::move(transform))
{
}


void StaticMeshRenderProxy::Render(const RenderSingleViewContext& viewContext)
{
    RenderSingleObjectContext objectContext;
    objectContext.ConstantBufferPerObject = ConstantBufferPerObject_;

    Mesh_->Render(viewContext, objectContext);
}

void StaticMeshRenderProxy::InitRHIResource()
{
    Mesh_->InitRHIResource();

    ConstantBufferPerObject buffer;
    buffer.WorldMatrix = Transform_.GetWorldMatrix();
    ConstantBufferPerObject_ = std::make_shared<ConstantBuffer<ConstantBufferPerObject>>(buffer);
}

void StaticMeshRenderProxy::UpdateTransform(const Transform& transform)
{
    Transform_ = transform;

    ConstantBufferPerObject buffer;
    buffer.WorldMatrix = Transform_.GetWorldMatrix();
    ConstantBufferPerObject_->UpdateBuffer(buffer);
}

