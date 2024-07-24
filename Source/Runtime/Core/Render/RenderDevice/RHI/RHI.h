#pragma once
#include "RHICommon.h"
#include "Runtime/Core/Misc/ApplicationInitParam.h"
#include "Runtime/Core/Misc/WindowHandler.h"
#include "Runtime/Foundation/Foundation.h"
#include "RHIVertexDeclaration.h"
#include "RHIShader.h"
#include "RHIConstantBuffer.h"
#include "RHIRenderTargetView.h"
#include "RHIVertexBuffer.h"
#include "RHIIndexBuffer.h"
#include "RHIBoundShaderState.h"
#include "RHITexture.h"

#include <boost/filesystem.hpp>


using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class RHI
    {
    public:

        /**
         * Framework
         */
        RHI() = default;
        virtual ~RHI() = default;
        virtual void InitRHI(const ApplicationInitParam& param, const WindowHandler& windowHandler) = 0;
        virtual void UnInitRHI() = 0;
        virtual RHITexture* GetBackBufferRT() = 0;

        /**
         * State
         */
    public:
        virtual void ClearRenderTarget(RHIRenderTargetView* rtv, const Vector4f& color) = 0;
        virtual void IASetPrimitiveTopology(RHIPrimitiveTopology pt) = 0;
        virtual void IASetVertexBuffer(uint32 slot, RHIVertexBuffer* vb, uint32 strike, uint32 offset) = 0;
        virtual void IASetIndexBuffer(RHIIndexBuffer* ib, uint32 offset) = 0;
        virtual void RSSetViewport(float left, float top, float width, float height) = 0;
        virtual void RSSetScissorRect(int32 left, int32 top, int32 right, int32 bottom) = 0;
        virtual void SetBoundShaderState(RHIBoundShaderState* state) = 0;
        virtual void SetShaderConstantBuffer(RHIGraphicsShader* shader, int slot, const std::shared_ptr<RHIConstantBuffer>& cb) = 0;
        virtual void OMSetRenderTarget(RHIRenderTargetView* rtv) = 0;

        /**
         * draw
         */
        virtual void DrawIndexedPrimitive(uint32 indexCount, uint32 startOffset, int vertexOffset) = 0;
        virtual void Present() = 0;

        /**
         * Resource
         */
    public:
        virtual std::shared_ptr<RHIVertexDeclaration> CreateVertexDeclaration(const std::vector<VertexDeclarationElement>& elements) = 0;
        virtual std::shared_ptr<RHIVertexBuffer> CreateVertexBuffer(RHIVertexBufferCreateInfo& createInfo) = 0;
        virtual std::shared_ptr<RHIIndexBuffer> CreateIndexBuffer(RHIIndexBufferCreateInfo& createInfo) = 0;
        virtual std::shared_ptr<RHIConstantBuffer> CreateConstantBuffer(RHIConstantBufferCreateInfo& createInfo) = 0;
        virtual std::shared_ptr<RHIVertexShader> CreateVertexShader(const ShaderByteCodeBlob& blob) = 0;
        virtual std::shared_ptr<RHIVertexShader> CreateVertexShader(const boost::filesystem::path& fp) = 0;
        virtual std::shared_ptr<RHIPixelShader> CreatePixelShader(const ShaderByteCodeBlob& blob) = 0;
        virtual std::shared_ptr<RHIPixelShader> CreatePixelShader(const boost::filesystem::path& fp) = 0;
        virtual std::shared_ptr<RHIBoundShaderState> CreateBoundShaderState(const std::shared_ptr<RHIVertexDeclaration>& vd, const std::shared_ptr<RHIVertexShader>& vs, const std::shared_ptr<RHIPixelShader>& ps) = 0;
        virtual std::shared_ptr<RHITexture> CreateRHITexture(const RHITextureCreateInfo& createInfo) = 0;
        virtual void CopyResource(RHITexture* dst, RHITexture* src) = 0;
        virtual void UpdateConstantBuffer(RHIConstantBuffer* buffer, uint8* data, uint32 size) = 0;

    };
}


