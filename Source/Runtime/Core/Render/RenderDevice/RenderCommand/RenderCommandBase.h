#pragma once
#include <memory>

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



    template<typename LAMBDA>
    class RenderCommandLambda : public RenderCommandBase
    {
    public:
        explicit RenderCommandLambda(LAMBDA&& lambda) : Lambda_(std::forward<LAMBDA>(lambda))
        {
        }

        ~RenderCommandLambda() override = default;

        void Execute(RHI *rhi) override
        {
            Lambda_();
        }


    private:
        LAMBDA Lambda_;
    };

}

