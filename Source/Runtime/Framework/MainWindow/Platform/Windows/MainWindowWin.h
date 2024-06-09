#if MIKASA_TARGET_PLATFORM_Window

#pragma once

#include "../../MainWindow.h"

// boost abi mismatch problem require boost header before <windows.h>
#define UNICODE
#include <windows.h>
#undef UNICODE


namespace mikasa::Runtime::Framework
{
    class MainWindowWin : public MainWindow
    {
    public:
        explicit MainWindowWin(Application* application, const ApplicationInitParam& info);
        ~MainWindowWin() override;

        WindowHandler GetInternalWindowHandler() override;

    private:
        static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    private:
        WNDCLASSEX  WNDCLASS_;
        HWND HWND_;

    };
}

#endif