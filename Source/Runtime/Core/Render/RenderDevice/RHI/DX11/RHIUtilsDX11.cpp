
#include "RHIUtilsDX11.h"

using namespace mikasa::Runtime::Core;

DXGI_FORMAT RHIUtilsDX11::ConvertPixelFormat(mikasa::Runtime::Core::PixelFormat pf)
{
    switch (pf)
    {
        case PixelFormat::PF_R8G8B8A8_UNorm:
            return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
        default:
            MIKASA_ASSERT(false);
            throw;
    }
}
