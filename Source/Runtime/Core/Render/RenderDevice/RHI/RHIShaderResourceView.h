#pragma once
#include "RHIResource.h"

namespace mikasa::Runtime::Core
{
    class RHIShaderResourceView : public RHIResource
    {
    public:
        RHIShaderResourceView();
        ~RHIShaderResourceView() override;
    };

}
