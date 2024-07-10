#ifdef MIKASA_TARGET_PLATFORM_Window

#include "WindowsApplication.h"
#include <windows.h>

using namespace mikasa::Runtime::Framework;

static WindowsApplication* Instance_ = nullptr;

void WindowsApplication::Init(const ApplicationInitParam& param)
{
    Instance_ = this;
    Application::Init(param);
}

void WindowsApplication::UnInit()
{
    Application::UnInit();
    Instance_ = nullptr;
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

LRESULT WindowsApplication::GlobalWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return Instance_->InstanceWndProcHandler(hWnd, msg, wParam, lParam);
}

LRESULT WindowsApplication::InstanceWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_DESTROY:
        {
            ::PostQuitMessage(0);
            return 0;
        }
        default:
        {
            return ::DefWindowProcW(hWnd, msg, wParam, lParam);
        }
    }
}

#endif