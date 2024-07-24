#pragma once
#include "RenderResource.h"
#include "../RHI/RHIConstantBuffer.h"
#include "../RHI/RHICommon.h"
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

        void UpdateBuffer(const BufferStruct& cpuBuffer);

    private:
        BufferStruct CpuBuffer_;
        std::shared_ptr<RHIConstantBuffer> GpuBuffer_;
    };

    template<typename BufferStruct>
    ConstantBuffer<BufferStruct>::ConstantBuffer(const BufferStruct& content)
        : CpuBuffer_(content)
    {
        RHIConstantBufferCreateInfo info(&content, sizeof(content));
        GpuBuffer_ = RenderDevice::RHI->CreateConstantBuffer(info);
    }

    template<typename BufferStruct>
    void ConstantBuffer<BufferStruct>::UpdateBuffer(const BufferStruct &cpuBuffer)
    {
        CpuBuffer_ = cpuBuffer;
        RenderDevice::RHI->UpdateConstantBuffer(GpuBuffer_.get(), (uint8*)&cpuBuffer, sizeof(cpuBuffer));
    }


}

