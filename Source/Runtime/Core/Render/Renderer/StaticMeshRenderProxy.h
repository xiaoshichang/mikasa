#pragma once

#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class StaticMeshRenderProxy
    {
    public:
        explicit StaticMeshRenderProxy(const Matrix4x4f& worldMatrix);
        const Matrix4x4f& GetWorldMatrix();
        void UpdateWorldMatrix(const Matrix4x4f& worldMatrix);

    private:
        Matrix4x4f WorldMatrix_ = Matrix4x4f::Identity();

    };
}
