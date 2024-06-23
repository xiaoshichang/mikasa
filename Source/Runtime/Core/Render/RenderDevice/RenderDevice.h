#pragma once
#include "Runtime/Core/Misc/ApplicationInitParam.h"
#include "Runtime/Core/Misc/WindowHandler.h"
#include "Runtime/Core/Render/RenderDevice/RenderCommand/RenderCommandBase.h"
#include "Runtime/Core/Render/RenderDevice/RenderCommand/RenderCommandQueue.h"
#include "RHI/RHI.h"


namespace mikasa::Runtime::Core
{
    class RenderDevice
    {
    public:
        static void Init(const ApplicationInitParam& param, const WindowHandler& windowHandler);
        static void UnInit();


        ///////////////// render command /////////////////////
    public:
        static bool ProcessOneRenderCommand();
        static void FlushAllRenderCommand();
        static void EnqueueOneRenderCommand(RenderCommandBase* command);
        static RenderCommandBase* Dequeue();
    private:
        static RenderCommandQueue* RenderCommandQueue_;

        //////////////// rhi ////////////////////
    public:
        static RHI* RHI;
    };

#define ENQUEUE_LAMBDA_RENDER_COMMAND(L) \
    auto command = new RenderCommandLambda(std::move(lambda));  \
    RenderDevice::EnqueueOneRenderCommand(command);
}

