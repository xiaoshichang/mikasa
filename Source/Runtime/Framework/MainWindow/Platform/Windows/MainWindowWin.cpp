#if MIKASA_TARGET_PLATFORM_Window

#include "MainWindowWin.h"

using namespace mikasa::Runtime::Framework;

MainWindowWin::MainWindowWin(Application* application, const ApplicationInitParam &info)
    : MainWindow(application)
    , HWND_(nullptr)
    , WNDCLASS_()
{
    WNDCLASS_ =
        {
            sizeof(WNDCLASS_),
            CS_CLASSDC,
            WndProc,
            0L,
            0L,
            GetModuleHandle(nullptr),
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            TEXT("mikasa"),
            nullptr
        };
    ::RegisterClassEx(&WNDCLASS_);
    auto style = WS_OVERLAPPEDWINDOW;
    if (!info.WindowResizeable)
    {
        style = style ^ WS_THICKFRAME;
    }

    std::wstring title = std::wstring(info.WindowTitle.begin(), info.WindowTitle.end());
    HWND_ = ::CreateWindowEx(
            NULL,
            WNDCLASS_.lpszClassName,
            title.c_str(),
            style,
            info.WindowOffsetX,
            info.WindowOffsetY,
            info.WindowWidth,
            info.WindowHeight,
            nullptr,
            nullptr,
            WNDCLASS_.hInstance,
            nullptr
    );

    ::ShowWindow(HWND_, SW_SHOWDEFAULT);
    ::UpdateWindow(HWND_);

    // Registering to Receive Windows Touch Input
    ::RegisterTouchWindow(HWND_, 0);
}

LRESULT MainWindowWin::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

MainWindowWin::~MainWindowWin()
{
    ::UnregisterClass(WNDCLASS_.lpszClassName, WNDCLASS_.hInstance);
}

#endif