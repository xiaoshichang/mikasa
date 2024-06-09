#pragma once

namespace mikasa::Runtime::Core
{

    class RenderCommandQueue;
    class RenderCommandCreator
    {
    public:
        static void Init(RenderCommandQueue* queue);
        static void UnInit();
        static void Enqueue_SetViewportCmd();

    private:
        static RenderCommandQueue* CommandQueue_;

    };

}

