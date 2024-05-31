#pragma once

#include "Runtime/Foundation/MultiThread.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Module
{
    class RenderThreadRunnable : public Runnable
    {
    public:
        RenderThreadRunnable() = default;
        ~RenderThreadRunnable() override = default ;

    public:
        bool Init() override;

        uint32 Run() override;

        void Exit() override;

        void Stop() override;

    };
}