#pragma once

#include "imgui.h"
#include <memory>

namespace mikasa::Editor
{
    class EditorGUI
    {
    public:
        static void Init();
        static void StartFrame();
        static void EndFrame();
        static void Render();

        static void DrawDemoWindow();


    private:
        static std::shared_ptr<ImDrawData> CopyDrawDataForRender(const ImDrawData* data);
        static void ReleaseDrawDataAfterRender(const std::shared_ptr<ImDrawData>& data);
    };
}

