#pragma once

namespace mikasa::Runtime::Core
{
    class RenderResource
    {
    public:
        RenderResource() = default;
        virtual ~RenderResource() = default;

        virtual void InitRHIResource() = 0;
    };
}

