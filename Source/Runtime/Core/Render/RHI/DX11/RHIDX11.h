#ifdef MIKASA_TARGET_PLATFORM_Window
#pragma once

#include "../RHI.h"
#include <d3d11.h>
#include <Windows.h>
#include <dxgi1_4.h>


namespace mikasa::Runtime::Core
{
    class RHIDX11 : public RHI
    {
    public:
        ~RHIDX11() override = default;
        void InitRHI(const ApplicationInitParam &param, const WindowHandler &windowHandler) override;
        void UnInitRHI() override;
        RHIRenderTargetView* GetBackBufferRTV() override;

    private:
        void CreateDevice();
        void ReleaseDevice();
        void CreateSwapChain(const ApplicationInitParam& param, const WindowHandler& windowHandler);
        void ReleaseSwapChain();
        void CreateBackBufferRTV();
        void ReleaseBackBufferRTV();

    public:
        void RSSetViewport(float left, float top, float width, float height) override;
        void RSSetScissorRect(int32 left, int32 top, int32 right, int32 bottom) override;
        void ClearRenderTarget(RHIRenderTargetView* rtv, const Vector4f& color) override;
        void Present() override;


    private:
        ID3D11Device* Device_ = nullptr;
        ID3D11DeviceContext* Context_ = nullptr;
        IDXGISwapChain1* SwapChain_ = nullptr;

        /**
         * represent the swap chain back buffer for rendering.
         */
        RHIRenderTargetView* BackBufferRTV_ = nullptr;
    };

}



#endif