//#ifdef MIKASA_TARGET_PLATFORM_Window
//
//#include "RHIDX12.h"
//
//#include <windows.h>
//#include <d3d12.h>
//#include <dxgi1_6.h>
//#include <wrl.h>
//
//using namespace mikasa::Runtime::Core;
//using namespace Microsoft::WRL;
//
//void RHIDX12::InitRHI(const ApplicationInitParam& param, const WindowHandler& windowHandler)
//{
//    CreateDevice();
//    CreateCommandQueue();
//    CreateSwapChain(param, windowHandler);
//    CreateFrameContext();
//    CreateCommandList();
//    CreateFence();
//
//}
//
//void RHIDX12::UnInitRHI()
//{
//    ReleaseFence();
//    ReleaseCommandList();
//    ReleaseFrameContext();
//    ReleaseSwapChain();
//    ReleaseCommandQueue();
//    ReleaseDevice();
//}
//
//void RHIDX12::CreateDevice()
//{
//    ComPtr<IDXGIFactory4> dxgiFactory;
//    ComPtr<IDXGIAdapter1> dxgiAdapter1;
//    ComPtr<IDXGIAdapter4> dxgiAdapter4;
//
//    UINT createFactoryFlags = 0;
//#ifdef MIKASA_BUILDTYPE_DEBUG
//    ComPtr<ID3D12Debug> debugController;
//    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
//    {
//        debugController->EnableDebugLayer();
//        createFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
//    }
//#endif
//    if (FAILED(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory))))
//    {
//        throw ;
//    }
//
//    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
//    SIZE_T maxDedicatedVideoMemory = 0;
//    for (UINT i = 0; dxgiFactory->EnumAdapters1(i, &dxgiAdapter1) != DXGI_ERROR_NOT_FOUND; ++i)
//    {
//        DXGI_ADAPTER_DESC1 dxgiAdapterDesc1;
//        dxgiAdapter1->GetDesc1(&dxgiAdapterDesc1);
//
//        auto hardware = (dxgiAdapterDesc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0;
//        auto success = SUCCEEDED(D3D12CreateDevice(dxgiAdapter1.Get(),featureLevel, __uuidof(ID3D12Device), nullptr));
//        auto moreMemory = dxgiAdapterDesc1.DedicatedVideoMemory > maxDedicatedVideoMemory;
//        if (hardware && success && moreMemory)
//        {
//            maxDedicatedVideoMemory = dxgiAdapterDesc1.DedicatedVideoMemory;
//            if (FAILED(dxgiAdapter1.As(&dxgiAdapter4)))
//            {
//                throw;
//            }
//        }
//    }
//
//    if (FAILED(D3D12CreateDevice(dxgiAdapter4.Get(), featureLevel, IID_PPV_ARGS(&Device_))))
//    {
//        throw ;
//    }
//}
//
//void RHIDX12::ReleaseDevice()
//{
//    MIKASA_ASSERT(Device_ != nullptr);
//    Device_->Release();
//    Device_ = nullptr;
//}
//
//void RHIDX12::CreateCommandQueue()
//{
//    D3D12_COMMAND_QUEUE_DESC desc = {};
//    desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
//    desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
//    desc.NodeMask = 1;
//    if (FAILED(Device_->CreateCommandQueue(&desc, IID_PPV_ARGS(&CommandQueue_))))
//    {
//        throw;
//    }
//}
//
//void RHIDX12::ReleaseCommandQueue()
//{
//    MIKASA_ASSERT(CommandQueue_ != nullptr);
//    CommandQueue_->Release();
//    CommandQueue_ = nullptr;
//}
//
//void RHIDX12::CreateSwapChain(const ApplicationInitParam& param, const WindowHandler& windowHandler)
//{
//    int width, height;
//    if (param.EditorMode)
//    {
//        width = 0;
//        height = 0;
//    }
//    else
//    {
//        width = param.WindowWidth;
//        height = param.WindowHeight;
//    }
//    DXGI_SWAP_CHAIN_DESC1 sd;
//    {
//        ZeroMemory(&sd, sizeof(sd));
//        sd.BufferCount = NUM_BACK_BUFFERS;
//        sd.Width = width;
//        sd.Height = height;
//        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//        sd.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
//        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//        sd.SampleDesc.Count = 1;
//        sd.SampleDesc.Quality = 0;
//        sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
//        sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
//        sd.Scaling = DXGI_SCALING_STRETCH;
//        sd.Stereo = FALSE;
//    }
//
//    IDXGIFactory4* dxgiFactory = nullptr;
//    IDXGISwapChain1* swapChain1 = nullptr;
//    if (CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory)) != S_OK)
//    {
//        throw;
//    }
//
//    // For Direct3D 11, and earlier versions of Direct3D, this is a pointer to the Direct3D device for the swap chain.
//    // For Direct3D 12 this is a pointer to a direct command queue.
//    // https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nf-dxgi1_2-idxgifactory2-createswapchainforhwnd
//    if (dxgiFactory->CreateSwapChainForHwnd(
//            CommandQueue_,
//            windowHandler.HWND,
//            &sd,
//            nullptr,
//            nullptr,
//            &swapChain1) != S_OK)
//    {
//        throw;
//    }
//    if (swapChain1->QueryInterface(IID_PPV_ARGS(&SwapChain_)) != S_OK)
//    {
//        throw;
//    }
//
//    swapChain1->Release();
//    dxgiFactory->Release();
//    SwapChain_->SetMaximumFrameLatency(NUM_BACK_BUFFERS);
//    SwapChainWaitableObject_ = SwapChain_->GetFrameLatencyWaitableObject();
//
//}
//
//void RHIDX12::ReleaseSwapChain()
//{
//    if (SwapChainWaitableObject_)
//    {
//        CloseHandle(SwapChainWaitableObject_);
//        SwapChainWaitableObject_ = nullptr;
//    }
//    if (SwapChain_ != nullptr)
//    {
//        SwapChain_->SetFullscreenState(false, nullptr);
//        SwapChain_->Release();
//        SwapChain_ = nullptr;
//    }
//}
//
//void RHIDX12::CreateFence()
//{
//    if (Device_->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&Fence_)) != S_OK)
//    {
//        throw;
//    }
//    FenceEvent_ = CreateEvent(nullptr, FALSE, FALSE, nullptr);
//    if (FenceEvent_ == nullptr)
//    {
//        throw;
//    }
//}
//
//void RHIDX12::ReleaseFence()
//{
//    MIKASA_ASSERT(FenceEvent_ != nullptr);
//    CloseHandle(FenceEvent_);
//    FenceEvent_ = nullptr;
//
//    MIKASA_ASSERT(Fence_ != nullptr);
//    Fence_->Release();
//    Fence_ = nullptr;
//}
//
//void RHIDX12::CreateFrameContext()
//{
//    for (auto & frameContext : FrameContexts_)
//    {
//        frameContext = new FrameContextDX12();
//        if (Device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&frameContext->CommandAllocator)) != S_OK)
//        {
//            throw;
//        }
//    }
//}
//
//void RHIDX12::ReleaseFrameContext()
//{
//    for (auto frameContext : FrameContexts_)
//    {
//        if (frameContext->CommandAllocator)
//        {
//            frameContext->CommandAllocator->Release();
//            frameContext->CommandAllocator = nullptr;
//        }
//        delete frameContext;
//    }
//}
//
//void RHIDX12::CreateCommandList()
//{
//    MIKASA_ASSERT(CommandList_ == nullptr);
//    if (Device_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, FrameContexts_[0]->CommandAllocator, nullptr, IID_PPV_ARGS(&CommandList_)) != S_OK)
//    {
//        throw;
//    }
//    if (CommandList_->Close() != S_OK)
//    {
//        throw;
//    }
//}
//
//void RHIDX12::ReleaseCommandList()
//{
//    MIKASA_ASSERT(CommandList_ != nullptr);
//    CommandList_->Release();
//    CommandList_ = nullptr;
//}
//
//
//#endif