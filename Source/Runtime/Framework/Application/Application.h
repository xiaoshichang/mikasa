#pragma once
#include "Runtime/Core/Misc/ApplicationInitParam.h"

using namespace mikasa::Runtime::Core;

namespace mikasa::Runtime::Framework
{
    class Application
    {
    public:
        virtual void Init(const ApplicationInitParam& info);
        virtual void UnInit();
        virtual void StartFrame();
        virtual void PreUpdate();
        virtual void Update();
        virtual void PostUpdate();
        virtual void Render();
        virtual void AfterRender();
        virtual void EndFrame();
        void Run();

    protected:
        void RequestQuit();
        virtual void DispatchOSMessage() = 0;

    private:
        bool IsApplicationQuit_ = false;

    public:
        static ApplicationInitParam Param;
    };
}







