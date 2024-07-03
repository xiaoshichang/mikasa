#pragma once

#include "RHIResource.h"
#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{

    class RHIShader : public RHIResource
    {
    public:
        RHIShader() = default;
        ~RHIShader() override = default;
    };

    enum GraphicsShaderType
    {
        Vertex,
        Pixel
    };

    struct ShaderByteCodeBlob
    {
        ShaderByteCodeBlob()
            : ByteCode(nullptr)
            , ByteCodeSize(0)
        {
        }

        uint8* ByteCode;
        uint32 ByteCodeSize;
    };

    class RHIGraphicsShader : public RHIShader
    {
    public:
        explicit RHIGraphicsShader(GraphicsShaderType type)
            : ShaderType_(type)
        {
        }

        ~RHIGraphicsShader() override = default;
        GraphicsShaderType GetShaderType() const { return ShaderType_; }

    private:
        GraphicsShaderType ShaderType_;
    };

    class RHIVertexShader : public RHIGraphicsShader
    {
    public:
        explicit RHIVertexShader() : RHIGraphicsShader(GraphicsShaderType::Vertex)
        {
        }
        ~RHIVertexShader() override = default;

    };

    class RHIPixelShader : public RHIGraphicsShader
    {
    public:
        explicit RHIPixelShader()
            : RHIGraphicsShader(GraphicsShaderType::Pixel)
        {
        }
        ~RHIPixelShader() override = default;
    };
}

