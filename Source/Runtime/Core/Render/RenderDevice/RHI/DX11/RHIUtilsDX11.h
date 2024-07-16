#pragma once

#include "../RHICommon.h"
#include <d3d11.h>

namespace mikasa::Runtime::Core
{
    class RHIUtilsDX11
    {
    public:
        static DXGI_FORMAT ConvertPixelFormat(PixelFormat pf);
    };
}

