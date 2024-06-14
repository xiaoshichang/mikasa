#pragma once


namespace mikasa::Runtime::Core
{
    class RHI;
    class RenderCommandBase
    {
    public:
        RenderCommandBase() = default;
        virtual ~RenderCommandBase() = default;
        virtual void Execute(RHI* rhi) = 0;
    };

}

