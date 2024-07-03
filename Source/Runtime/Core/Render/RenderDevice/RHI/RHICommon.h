
#pragma once

#include <utility>
#include <string>
#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    const int MaxVertexElementCount = 16;

    enum RHIPrimitiveTopology : int
    {
        UnDefine,
        PointList,
        LineList,
        LineStrip,
        TriangleList,
        TriangleStrip
    };

    enum VertexElementType : uint8
    {
        VET_None = 0,
        VET_Float1,
        VET_Float2,
        VET_Float3,
        VET_Float4,
        VET_UByte4N,
        VET_Color
    };

    enum IndexBufferElementType : uint8
    {
        IET_None = 0,
        IET_U16,
        IET_U32
    };

    struct RHIVertexBufferCreateInfo
    {
        RHIVertexBufferCreateInfo(uint8* cpuResource,
                                  uint32 cpuResourceSize,
                                  std::string debugName="")
            : CpuResourceAddr(cpuResource)
            , CpuResourceSize(cpuResourceSize)
            , DebugName(std::move(debugName))
        {
        }

        std::string DebugName;
        uint8* CpuResourceAddr;
        uint32 CpuResourceSize;

        void DiscardCpuResourceAfterCreateRHIResource()
        {
            delete[] CpuResourceAddr;
            CpuResourceAddr = nullptr;
            CpuResourceSize = 0;
        }
    };

    struct RHIIndexBufferCreateInfo
    {
        RHIIndexBufferCreateInfo(uint8* cpuResource,
                                 uint32 cpuResourceSize,
                                 IndexBufferElementType iet,
                                 std::string debugName="")
                : CpuResourceAddr(cpuResource)
                , CpuResourceSize(cpuResourceSize)
                , ElementType(iet)
                , DebugName(std::move(debugName))
        {
        }

        std::string DebugName;
        uint8* CpuResourceAddr;
        uint32 CpuResourceSize;
        IndexBufferElementType ElementType;

        void DiscardCpuResourceAfterCreateRHIResource()
        {
            delete[] CpuResourceAddr;
            CpuResourceAddr = nullptr;
            CpuResourceSize = 0;
            ElementType = IndexBufferElementType::IET_None;
        }
    };

    struct RHIConstantBufferCreateInfo
    {
        explicit RHIConstantBufferCreateInfo(const void* dataAddr, const uint32 dataSize)
            : CpuResourceAddr(dataAddr)
            , CpuResourceSize(dataSize)
        {
        }

        const void* CpuResourceAddr;
        const uint32 CpuResourceSize;

    };
}