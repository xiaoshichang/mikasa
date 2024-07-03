#pragma once
#include "RenderResource.h"
#include "../RHI/RHIConstantBuffer.h"
#include "Runtime/Core/Render/RenderDevice/RHI/RHICommon.h"
#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"
#include <memory>

namespace mikasa::Runtime::Core
{
    template<typename BufferStruct>
    class ConstantBuffer : public RenderResource
    {
    public:
        explicit ConstantBuffer(const BufferStruct& content);
        ~ConstantBuffer() override = default;

        void InitRHIResource() override
        {
            // do the job in constructor
        }

        const std::shared_ptr<RHIConstantBuffer>& GetRHIConstantBuffer()
        {
            return GpuBuffer_;
        }

    private:

        std::shared_ptr<RHIConstantBuffer> GpuBuffer_;
    };

    template<typename BufferStruct>
    ConstantBuffer<BufferStruct>::ConstantBuffer(const BufferStruct &content)
    {
        RHIConstantBufferCreateInfo info(&content, sizeof(content));
        GpuBuffer_ = RenderDevice::RHI->CreateConstantBuffer(info);
    }


}

