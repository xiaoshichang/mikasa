//
// Created by shichang.xiao on 2024/6/11.
//

#include "RHIDX11.h"
#include <wrl.h>

using namespace Microsoft::WRL;
using namespace mikasa::Runtime::Core;

void RHIDX11::InitRHI(const ::ApplicationInitParam &param, const WindowHandler &windowHandler)
{
    CreateDevice();
    CreateSwapChain(param, windowHandler);
}

void RHIDX11::UnInitRHI()
{
    ReleaseSwapChain();
    ReleaseDevice();
}

void RHIDX11::CreateDevice()
{
    UINT flags = 0;
#ifndef MIKASA_BUILDTYPE_DEBUG
    // this enables VERY USEFUL debug messages in debugger output
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    // Set the feature level to DirectX 11.
    D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0 };

    // Create the device and device context objects
    auto hr = D3D11CreateDevice(
            nullptr,    // let system decide which adapter to use
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            flags,
            levels,
            ARRAYSIZE(levels),
            D3D11_SDK_VERSION,
            &Device_,
            nullptr,
            &Context_);
    if (hr != S_OK)
    {
        throw;
    }

}

void RHIDX11::ReleaseDevice()
{
    MIKASA_ASSERT(Context_ != nullptr);
    Context_->Release();
    Context_ = nullptr;

    MIKASA_ASSERT(Device_ != nullptr);
    Device_->Release();
    Device_ = nullptr;
}

void RHIDX11::CreateSwapChain(const ApplicationInitParam& param, const WindowHandler& windowHandler)
{
    // First, convert our ID3D11Device1 into an IDXGIDevice1
    IDXGIDevice1 * dxgiDevice;
    auto hr = Device_->QueryInterface(__uuidof(IDXGIDevice1), (void **)&dxgiDevice);
    if (hr != S_OK)
    {
        throw;
    }

    // Second, use the IDXGIDevice1 interface to get access to the adapter
    ComPtr<IDXGIAdapter> dxgiAdapter;
    dxgiDevice->GetAdapter(&dxgiAdapter);

    // Third, use the IDXGIAdapter interface to get access to the factory
    ComPtr<IDXGIFactory2> dxgiFactory;
    dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), &dxgiFactory);

    // set up the swap chain description
    DXGI_SWAP_CHAIN_DESC1 scd = {0};
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // how the swap chain should be used
    scd.BufferCount = 2;                                  // a front buffer and a back buffer
    scd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;              // the most common swap chain format
    scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;    // the recommended flip mode
    scd.SampleDesc.Count = 1;

    hr = dxgiFactory->CreateSwapChainForHwnd(
            Device_,
            windowHandler.HWND,
            &scd,
            nullptr,
            nullptr,
            &SwapChain_);
    if (hr != S_OK)
    {
        throw;
    }
}

void RHIDX11::ReleaseSwapChain()
{
    MIKASA_ASSERT(SwapChain_ != nullptr);
    SwapChain_->Release();
    SwapChain_ = nullptr;
}
