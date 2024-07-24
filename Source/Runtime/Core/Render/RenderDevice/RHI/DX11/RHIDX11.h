#ifdef MIKASA_TARGET_PLATFORM_Window
#pragma once

#include "Runtime/Core/Render/RenderDevice/RHI/RHI.h"
#include <d3d11.h>
#include <dxgi1_4.h>
#include <windows.h>

namespace mikasa::Runtime::Core
{
    class RHIDX11 : public RHI
    {
    public:
        ~RHIDX11() override = default;
        void InitRHI(const ApplicationInitParam &param, const WindowHandler &windowHandler) override;
        void UnInitRHI() override;
        RHITexture* GetBackBufferRT() override;

    private:
        void CreateDevice();
        void ReleaseDevice();
        void CreateSwapChain(const ApplicationInitParam& param, const WindowHandler& windowHandler);
        void ReleaseSwapChain();
        void CreateBackBufferRT();
        void ReleaseBackBufferRT();
        void ReleaseBoundConstantBuffer();

        /**
         * state
         */
    public:
        void ClearRenderTarget(RHIRenderTargetView* rtv, const Vector4f& color) override;
        void IASetPrimitiveTopology(RHIPrimitiveTopology pt) override;
        void IASetVertexBuffer(uint32 slot, RHIVertexBuffer* vb, uint32 strike, uint32 offset) override;
        void IASetIndexBuffer(RHIIndexBuffer* ib, uint32 offset) override;
        void RSSetViewport(float left, float top, float width, float height) override;
        void RSSetScissorRect(int32 left, int32 top, int32 right, int32 bottom) override;
        void SetBoundShaderState(RHIBoundShaderState* state) override;
        void SetShaderConstantBuffer(RHIGraphicsShader* shader, int slot, const std::shared_ptr<RHIConstantBuffer>& cb) override;
        void OMSetRenderTarget(RHIRenderTargetView* rtv) override;

        /**
         * draw
         */
    public:
        void DrawIndexedPrimitive(uint32 indexCount, uint32 startOffset, int vertexOffset) override;
        void Present() override;

        /**
         * Resource
         */
    public:
        std::shared_ptr<RHIVertexDeclaration> CreateVertexDeclaration(const std::vector<VertexDeclarationElement>& elements) override;
        std::shared_ptr<RHIVertexBuffer> CreateVertexBuffer(RHIVertexBufferCreateInfo& createInfo) override;
        std::shared_ptr<RHIIndexBuffer> CreateIndexBuffer(RHIIndexBufferCreateInfo& createInfo) override;
        std::shared_ptr<RHIConstantBuffer> CreateConstantBuffer(RHIConstantBufferCreateInfo& createInfo) override;
        std::shared_ptr<RHIVertexShader> CreateVertexShader(const ShaderByteCodeBlob& blob) override;
        std::shared_ptr<RHIVertexShader> CreateVertexShader(const boost::filesystem::path& fp) override;
        std::shared_ptr<RHIPixelShader> CreatePixelShader(const ShaderByteCodeBlob& blob) override;
        std::shared_ptr<RHIPixelShader> CreatePixelShader(const boost::filesystem::path& fp) override;

        std::shared_ptr<RHIBoundShaderState> CreateBoundShaderState(const std::shared_ptr<RHIVertexDeclaration>& vd,
                                                                    const std::shared_ptr<RHIVertexShader>& vs,
                                                                    const std::shared_ptr<RHIPixelShader>& ps) override;

        std::shared_ptr<RHITexture> CreateRHITexture(const RHITextureCreateInfo& createInfo) override;
        void CopyResource(RHITexture* dst, RHITexture* src) override;
        void UpdateConstantBuffer(RHIConstantBuffer* buffer, uint8* data, uint32 size) override;


    public:
        ID3D11Device* GetDevice() { return Device_; }
        ID3D11DeviceContext* GetDeviceContext() { return Context_; }

    private:
        ID3D11Device* Device_ = nullptr;
        ID3D11DeviceContext* Context_ = nullptr;
        IDXGISwapChain1* SwapChain_ = nullptr;

        /**
         * represent the swap chain back buffer for rendering.
         */
        RHITexture* BackBufferRT_ = nullptr;

        /**
         * track currently bounded constant buffer
         */
        static const int MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE = 14;
        static const int STANDARD_SHADER_TYPE_COUNT = 6;
        std::shared_ptr<RHIConstantBuffer> BoundConstantBuffers_[STANDARD_SHADER_TYPE_COUNT][MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE];
    };

}



#endif