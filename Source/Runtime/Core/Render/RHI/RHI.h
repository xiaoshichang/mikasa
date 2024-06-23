#pragma once
#include "Runtime/Core/Misc/ApplicationInitParam.h"
#include "Runtime/Core/Misc/WindowHandler.h"
#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class RHIRenderTargetView;
    class RHI
    {
    public:
        RHI() = default;
        virtual ~RHI() = default;
        virtual void InitRHI(const ApplicationInitParam& param, const WindowHandler& windowHandler) = 0;
        virtual void UnInitRHI() = 0;
        virtual RHIRenderTargetView* GetBackBufferRTV() = 0;

    public:
        virtual void RSSetViewport(float left, float top, float width, float height) = 0;
        virtual void RSSetScissorRect(int32 left, int32 top, int32 right, int32 bottom) = 0;

        virtual void ClearRenderTarget(RHIRenderTargetView* rtv, const Vector4f& color) = 0;


    public:
        virtual void Present() = 0;


    };
}


