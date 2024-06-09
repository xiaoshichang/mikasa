#ifdef MIKASA_TARGET_PLATFORM_Window
#pragma once

#include "../RHI.h"
#include <d3d12.h>
#include <dxgi1_6.h>


namespace mikasa::Runtime::Core
{
    struct FrameContextDX12
    {
        ID3D12CommandAllocator* CommandAllocator = nullptr;
        UINT64 FenceValue = 0;
    };

    class RHIDX12 : public RHI
    {
    public:
        RHIDX12() = default;
        ~RHIDX12() override = default;
        void InitRHI(const ApplicationInitParam& param, const WindowHandler& windowHandler) override;
        void UnInitRHI() override;

    private:
        void CreateDevice();
        void ReleaseDevice();
        void CreateCommandQueue();
        void ReleaseCommandQueue();
        void CreateSwapChain(const ApplicationInitParam& param, const WindowHandler& windowHandler);
        void ReleaseSwapChain();
        void CreateFence();
        void ReleaseFence();
        void CreateFrameContext();
        void ReleaseFrameContext();
        void CreateCommandList();
        void ReleaseCommandList();


    private:
        static const int NUM_BACK_BUFFERS = 2;

    private:
        ID3D12Device* Device_ = nullptr;
        ID3D12CommandQueue* CommandQueue_ = nullptr;
        ID3D12GraphicsCommandList* CommandList_ = nullptr;
        IDXGISwapChain3* SwapChain_ = nullptr;
        HANDLE SwapChainWaitableObject_ = nullptr;
        ID3D12Fence* Fence_ = nullptr;
        HANDLE FenceEvent_ = nullptr;

        FrameContextDX12* FrameContexts_[NUM_BACK_BUFFERS];


    };
}
#endif

