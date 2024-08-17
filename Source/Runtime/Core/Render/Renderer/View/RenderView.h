#pragma once
#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Core/Scene/Component/CameraCmpt.h"
#include "Runtime/Core/Render/RenderDevice/RenderResource/ConstantBuffer.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{

    struct ConstantBufferPerView
    {
        Matrix4x4f ViewMatrix;
        Matrix4x4f ProjectionMatrix;
    };

    struct RenderViewInitializer
    {
        Camera Camera;
        Matrix4x4f ViewMatrix;
        Matrix4x4f ProjectionMatrix;
    };

    /**
     * represents a "camera" in render thread.
     * construct on main thread and copy to render thread.
     */
    class RenderView
    {
    public:
        explicit RenderView(const RenderViewInitializer& initializer);
        void InitRHIResource();
        ConstantBuffer<ConstantBufferPerView>* GetConstantBufferPerView();

    public:
        Camera Camera;
        ConstantBufferPerView ConstantBufferPerViewData_;
        std::shared_ptr<ConstantBuffer<ConstantBufferPerView>> ConstantBufferPerView_;
    };
}

