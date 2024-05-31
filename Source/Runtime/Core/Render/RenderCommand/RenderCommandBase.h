#pragma once


namespace mikasa::Runtime::Core
{
    class RenderCommandBase
    {
    public:
        virtual void Execute() = 0;
    };

}

