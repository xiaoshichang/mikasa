#pragma once

#include "Runtime/Foundation/MultiThread.h"
#include "Runtime/Core/Render/RenderCommandQueue.h"

using namespace mikasa::Runtime::Foundation;
using namespace mikasa::Runtime::Core;

namespace mikasa::Runtime::Module
{

    struct RenderThreadRunnableInitParam
    {
        RenderCommandQueue* RenderCommandQueue;
    };

    class RenderThreadRunnable : public Runnable
    {
    public:
        explicit RenderThreadRunnable(const RenderThreadRunnableInitParam& param);
        ~RenderThreadRunnable() override = default ;

    public:
        bool Init() override;

        uint32 Run() override;

        void Exit() override;

        void Stop() override;

    private:
        bool Rendering_ = true;
        RenderCommandQueue* RenderCommandQueue_;
    };
}