#ifdef MIKASA_TARGET_PLATFORM_Window

#pragma once
#include "Runtime/Application/ApplicationBase.h"

namespace mikasa::Runtime::Application
{
    class WindowsApplication : public ApplicationBase
    {
    public:
        void Init(const ApplicationInitParam& info) override;
        void UnInit() override;
    };
}

#endif

