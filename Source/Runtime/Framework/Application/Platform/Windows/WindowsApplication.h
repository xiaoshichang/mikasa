#ifdef MIKASA_TARGET_PLATFORM_Window

#pragma once
#include "../../Application.h"
#include <windows.h>

namespace mikasa::Runtime::Framework
{

    class WindowsApplication : public Application
    {
    public:
        void Init(const ApplicationInitParam& info) override;
        void UnInit() override;
        static LRESULT GlobalWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    protected:
        void DispatchOSMessage() override;
        virtual LRESULT InstanceWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    };
}

#endif

