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

    private:
        void CreateDevice();
        void ReleaseDevice();
        void CreateSwapChain(const ApplicationInitParam& param, const WindowHandler& windowHandler);
        void ReleaseSwapChain();


    private:
        ID3D11Device* Device_ = nullptr;
        ID3D11DeviceContext* Context_ = nullptr;
        IDXGISwapChain1* SwapChain_ = nullptr;
    };

}



#endif