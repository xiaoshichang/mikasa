#if MIKASA_TARGET_PLATFORM_Window

#pragma once
#include "Runtime/Framework/Application/Platform/Windows/WindowsApplication.h"

using namespace mikasa::Runtime::Framework;

namespace mikasa::Editor
{
    class WindowsEditor : public WindowsApplication
    {
    public:
        void Init(const ApplicationInitParam& info) override;
    };

}

#endif