#pragma once

#include "Runtime/Foundation/MultiThread.h"
#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"
#include "Runtime/Core/Misc/ApplicationInitParam.h"
#include "Runtime/Core/Misc/WindowHandler.h"

using namespace mikasa::Runtime::Foundation;
using namespace mikasa::Runtime::Core;

namespace mikasa::Runtime::Module
{

    struct RenderThreadRunnableInitParam
    {
        ApplicationInitParam ApplicationInitParam;
        WindowHandler WindowHandler;
    };

    class RenderThreadRunnable : public Runnable
    {
    public:
        explicit RenderThreadRunnable(RenderThreadRunnableInitParam  param);
        ~RenderThreadRunnable() override = default ;

    public:
        bool Init() override;

        uint32 Run() override;

        void Exit() override;

        void Stop() override;

    private:
        bool Rendering_ = true;
        RenderThreadRunnableInitParam InitParam_;
    };
}