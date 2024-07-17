#include "Runtime/Foundation/Foundation.h"
#include "RHIShaderResourceViewDX11.h"

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

RHIShaderResourceViewDX11::RHIShaderResourceViewDX11(ID3D11Device* device, ID3D11Resource* resource)
{
    D3D11_SHADER_RESOURCE_VIEW_DESC desc;
    desc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_SRV_DIMENSION::D3D10_1_SRV_DIMENSION_TEXTURE2D;;
    desc.Texture2D.MipLevels = 1;
    desc.Texture2D.MostDetailedMip = 0;
    if (device->CreateShaderResourceView(resource, &desc, &Internal_) != S_OK)
    {
        MIKASA_ASSERT(false);
    }
}

RHIShaderResourceViewDX11::~RHIShaderResourceViewDX11()
{
    Internal_->Release();
    Internal_ = nullptr;
}

ID3D11ShaderResourceView *RHIShaderResourceViewDX11::GetInternal()
{
    return Internal_;
}
