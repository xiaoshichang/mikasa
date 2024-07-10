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

        void StartFrame() override;
        void Render() override;
        void EndFrame() override;
        LRESULT InstanceWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;


    };

}

#endif