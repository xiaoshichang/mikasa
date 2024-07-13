#pragma once

#include "imgui.h"


#include <memory>
#include <windows.h>

namespace mikasa::Runtime::Core
{
    class GameObject;
}

namespace mikasa::Editor
{
    class MainMenuBar;
    class Panel;
    class Editor
    {
    public:
        static void Init();
        static void UnInit();
        static void StartFrame();
        static void EndFrame();
        static void Render();
        static void DrawDemoWindow();
        static bool InstanceWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    private:
        static std::shared_ptr<ImDrawData> CopyDrawDataForRender(const ImDrawData* data);
        static void ReleaseDrawDataAfterRender(const std::shared_ptr<ImDrawData>& data);

    public:
        static MainMenuBar* Menu;
        static Panel* Hierarchy;
        static Panel* Inspector;
        static Panel* Game;
        static Panel* Scene;
        static Runtime::Core::GameObject* CurrentSelectedGameObject;
    };
}

