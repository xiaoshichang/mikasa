
#include "StaticMeshRenderProxy.h"

using namespace mikasa::Runtime::Core;

StaticMeshRenderProxy::StaticMeshRenderProxy(const Matrix4x4f &worldMatrix)
    : WorldMatrix_(worldMatrix)
{
}

const Matrix4x4f &StaticMeshRenderProxy::GetWorldMatrix()
{
    return WorldMatrix_;
}

void StaticMeshRenderProxy::UpdateWorldMatrix(const Matrix4x4f &worldMatrix)
{
    WorldMatrix_ = worldMatrix;
}
