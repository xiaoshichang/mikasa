#ifdef MIKASA_TARGET_PLATFORM_Window

#pragma once
#include "../../Application.h"

namespace mikasa::Runtime::Framework
{
    class WindowsApplication : public Application
    {
    public:
        void Init(const ApplicationInitParam& info) override;
        void UnInit() override;

    protected:
        void DispatchOSMessage() override;
    };
}

#endif

