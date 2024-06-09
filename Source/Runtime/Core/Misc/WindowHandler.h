#pragma once

#if MIKASA_TARGET_PLATFORM_Window
#include <windows.h>
#endif

namespace mikasa::Runtime::Core
{
    struct WindowHandler
    {
#if MIKASA_TARGET_PLATFORM_Window
        HWND HWND = nullptr;
#endif
    };
}
