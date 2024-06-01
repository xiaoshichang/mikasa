#ifdef MIKASA_TARGET_PLATFORM_Window

#include "WindowsApplication.h"
#include <windows.h>

using namespace mikasa::Runtime::Framework;

void WindowsApplication::Init(const ApplicationInitParam& param)
{
    Application::Init(param);
}

void WindowsApplication::UnInit()
{
    Application::UnInit();
}

void WindowsApplication::DispatchOSMessage()
{
    MSG msg;
    while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);

        if (msg.message == WM_QUIT)
        {
            RequestQuit();
        }
    }
}

#endif