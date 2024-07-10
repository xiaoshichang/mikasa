
#include "WindowsEditor.h"
#include "Runtime/Module/SceneModule/SceneModule.h"
#include "Editor/EditorGUI/EditorGUI.h"

using namespace mikasa::Editor;
using namespace mikasa::Runtime::Module;

void WindowsEditor::Init(const ApplicationInitParam &info)
{
    WindowsApplication::Init(info);
    EditorGUI::Init();

    SceneModule::SyncLoadScene("");
}

void WindowsEditor::StartFrame()
{
    Application::StartFrame();
    EditorGUI::StartFrame();
}

void WindowsEditor::Render()
{
    EditorGUI::Render();


    auto lambda = []()
    {
        RenderDevice::RHI->Present();
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}

void WindowsEditor::EndFrame()
{
    EditorGUI::EndFrame();
    Application::EndFrame();
}

LRESULT WindowsEditor::InstanceWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (EditorGUI::InstanceWndProcHandler(hWnd, msg, wParam, lParam))
    {
        return true;
    }
    return WindowsApplication::InstanceWndProcHandler(hWnd, msg, wParam, lParam);
}


