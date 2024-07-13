
#include "WindowsEditor.h"
#include "Runtime/Module/SceneModule/SceneModule.h"
#include "Editor/Editor/Editor.h"

using namespace mikasa::Editor;
using namespace mikasa::Runtime::Module;

void WindowsEditor::Init(const ApplicationInitParam &info)
{
    WindowsApplication::Init(info);
    Editor::Init();

    SceneModule::SyncLoadScene("");
}

void WindowsEditor::StartFrame()
{
    Application::StartFrame();
    Editor::StartFrame();
}

void WindowsEditor::Render()
{
    Editor::Render();


    auto lambda = []()
    {
        RenderDevice::RHI->Present();
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}

void WindowsEditor::EndFrame()
{
    Editor::EndFrame();
    Application::EndFrame();
}

LRESULT WindowsEditor::InstanceWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (Editor::InstanceWndProcHandler(hWnd, msg, wParam, lParam))
    {
        return true;
    }
    return WindowsApplication::InstanceWndProcHandler(hWnd, msg, wParam, lParam);
}

void WindowsEditor::UnInit()
{
    Editor::UnInit();
    WindowsApplication::UnInit();
}


