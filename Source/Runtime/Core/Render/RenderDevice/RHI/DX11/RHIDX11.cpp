#ifdef MIKASA_TARGET_PLATFORM_Window

#include "RHIDX11.h"
#include "RHIRenderTargetViewDX11.h"
#include "RHIVertexBufferDX11.h"
#include "RHIIndexBufferDX11.h"
#include "RHIVertexDeclarationDX11.h"
#include "RHIShaderDX11.h"
#include "RHIBoundShaderStateDX11.h"
#include "RHIConstantBufferDX11.h"

#include <wrl.h>

using namespace mikasa::Runtime::Core;

void RHIDX11::InitRHI(const ::ApplicationInitParam &param, const WindowHandler &windowHandler)
{
    CreateDevice();
    CreateSwapChain(param, windowHandler);
    CreateBackBufferRTV();
}

void RHIDX11::UnInitRHI()
{
    ReleaseBoundConstantBuffer();
    ReleaseBackBufferRTV();
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
    Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
    dxgiDevice->GetAdapter(&dxgiAdapter);

    // Third, use the IDXGIAdapter interface to get access to the factory
    Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory;
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

void RHIDX11::CreateBackBufferRTV()
{
    ID3D11Resource* pBackBuffer = nullptr;
    ID3D11RenderTargetView* rtv = nullptr;

    if (SwapChain_->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer)) != S_OK)
    {
        throw;
    }
    BackBufferRTV_ = new RHIRenderTargetViewDX11(Device_, pBackBuffer);
}

void RHIDX11::ReleaseBackBufferRTV()
{
    delete BackBufferRTV_;
    BackBufferRTV_ = nullptr;
}

void RHIDX11::ReleaseBoundConstantBuffer()
{
    for(int i = 0; i < STANDARD_SHADER_TYPE_COUNT; ++i)
    {
        for(int j = 0; j < MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE; ++j)
        {
            BoundConstantBuffers_[i][j].reset();
        }
    }
}

RHIRenderTargetView* RHIDX11::GetBackBufferRTV()
{
    return BackBufferRTV_;
}

void RHIDX11::ClearRenderTarget(RHIRenderTargetView* rtv, const Vector4f& color)
{
    auto* rtvDX11 = dynamic_cast<RHIRenderTargetViewDX11 *>(rtv);
    Context_->ClearRenderTargetView(rtvDX11->GetInternal(), (const float*)color);
}

void RHIDX11::IASetPrimitiveTopology(RHIPrimitiveTopology pt)
{
    if (pt == RHIPrimitiveTopology::TriangleStrip)
    {
        Context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    }
    else if (pt == RHIPrimitiveTopology::TriangleList)
    {
        Context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }
    else if (pt == RHIPrimitiveTopology::LineList)
    {
        Context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    }
    else if (pt == RHIPrimitiveTopology::LineStrip)
    {
        Context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
    }
    else if (pt == RHIPrimitiveTopology::PointList)
    {
        Context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
    }
    else
    {
        MIKASA_ASSERT(false);
    }
}

void RHIDX11::IASetVertexBuffer(uint32 slot, RHIVertexBuffer* vb, uint32 strike, uint32 offset)
{
    auto internal = ((RHIVertexBufferDX11*)vb)->GetInternal();
    Context_->IASetVertexBuffers(slot, 1, &internal, &strike, &offset);
}

void RHIDX11::IASetIndexBuffer(RHIIndexBuffer *ib, uint32 offset)
{
    auto ib_ = ((RHIIndexBufferDX11*)ib);
    auto internal = ib_->GetInternal();
    Context_->IASetIndexBuffer(internal, ib_->GetFormat(), offset);
}

void RHIDX11::RSSetViewport(float left, float top, float width, float height)
{
    D3D11_VIEWPORT  viewport(left, top, width, height, 0, 1);
    Context_->RSSetViewports(1, &viewport);
}

void RHIDX11::RSSetScissorRect(int32 left, int32 top, int32 right, int32 bottom)
{
    D3D11_RECT rect(left, top, right, bottom);
    Context_->RSSetScissorRects(1, &rect);
}

void RHIDX11::SetBoundShaderState(RHIBoundShaderState* state)
{
    auto* stateDX11 = (RHIBoundShaderStateDX11*)state;
    stateDX11->Bind(Context_);
}

void RHIDX11::SetShaderConstantBuffer(RHIGraphicsShader* shader, int slot, const std::shared_ptr<RHIConstantBuffer>& cb)
{
    auto gst = shader->GetShaderType();
    auto internal = ((RHIConstantBufferDX11*)cb.get())->GetInternal();

    switch (gst)
    {
        case GraphicsShaderType::Vertex:
        {
            Context_->VSSetConstantBuffers(slot, 1, &internal);
            break;
        }
        case GraphicsShaderType::Pixel:
        {
            Context_->PSSetConstantBuffers(slot, 1, &internal);
            break;
        }
        default:
            throw;
    }
    BoundConstantBuffers_[gst][slot] = cb;
}

void RHIDX11::OMSetRenderTarget(RHIRenderTargetView* rtv)
{
    auto* rtvDX11 = (RHIRenderTargetViewDX11*)rtv;
    auto internal =  rtvDX11->GetInternal();
    Context_->OMSetRenderTargets(1, &internal, nullptr);
}

void RHIDX11::DrawIndexedPrimitive(uint32 indexCount, uint32 startOffset, int vertexOffset)
{
    Context_->DrawIndexed(indexCount, startOffset, vertexOffset);
}

void RHIDX11::Present()
{
    SwapChain_->Present(1, 0);
}

std::shared_ptr<RHIVertexDeclaration> RHIDX11::CreateVertexDeclaration(const std::vector<VertexDeclarationElement> &elements)
{
    auto vd = std::make_shared<RHIVertexDeclarationDX11>(elements );
    return vd;
}

std::shared_ptr<RHIVertexBuffer> RHIDX11::CreateVertexBuffer(RHIVertexBufferCreateInfo& createInfo)
{
    auto vb = std::make_shared<RHIVertexBufferDX11>(Device_, createInfo);
    createInfo.DiscardCpuResourceAfterCreateRHIResource();
    return vb;
}

std::shared_ptr<RHIIndexBuffer> RHIDX11::CreateIndexBuffer(RHIIndexBufferCreateInfo& createInfo)
{
    auto ib = std::make_shared<RHIIndexBufferDX11>(Device_, createInfo);
    createInfo.DiscardCpuResourceAfterCreateRHIResource();
    return ib;
}

std::shared_ptr<RHIConstantBuffer> RHIDX11::CreateConstantBuffer(RHIConstantBufferCreateInfo &createInfo)
{
    auto cb = std::make_shared<RHIConstantBufferDX11>(Device_, createInfo);
    return cb;
}


std::shared_ptr<RHIVertexShader> RHIDX11::CreateVertexShader(const ShaderByteCodeBlob& blob)
{
    auto vs = std::make_shared<RHIVertexShaderDX11>(Device_, blob);
    return vs;
}

std::shared_ptr<RHIVertexShader> RHIDX11::CreateVertexShader(const boost::filesystem::path& fp)
{
    auto vs = std::make_shared<RHIVertexShaderDX11>(Device_, fp);
    return vs;
}

std::shared_ptr<RHIPixelShader> RHIDX11::CreatePixelShader(const ShaderByteCodeBlob& blob)
{
    auto ps = std::make_shared<RHIPixelShaderDX11>(Device_, blob);
    return ps;
}

std::shared_ptr<RHIPixelShader> RHIDX11::CreatePixelShader(const boost::filesystem::path& fp)
{
    auto ps = std::make_shared<RHIPixelShaderDX11>(Device_, fp);
    return ps;
}

std::shared_ptr<RHIBoundShaderState> RHIDX11::CreateBoundShaderState(const std::shared_ptr<RHIVertexDeclaration> &vd,
                                                                     const std::shared_ptr<RHIVertexShader> &vs,
                                                                     const std::shared_ptr<RHIPixelShader> &ps)
{
    auto bss = std::make_shared<RHIBoundShaderStateDX11>(Device_, vd, vs, ps);
    return bss;
}




#endif