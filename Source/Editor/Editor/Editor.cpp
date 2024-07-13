
#include "Runtime/Framework/Application/Application.h"
#include "Runtime/Framework/MainWindow/MainWindow.h"
#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"
#include "Runtime/Core/Render/RenderDevice/RHI/DX11/RHIDX11.h"

#include "MenuBar/MainMenuBar.h"
#include "Panels/HierarchyPanel.h"
#include "Panels/InspectorPanel.h"
#include "Panels/GamePanel.h"
#include "Panels/ScenePanel.h"

#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"

#include "Editor.h"

using namespace mikasa::Editor;
using namespace mikasa::Runtime::Framework;

bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


MainMenuBar* Editor::Menu = nullptr;
Panel* Editor::Hierarchy = nullptr;
Panel* Editor::Inspector = nullptr;
Panel* Editor::Game = nullptr;
Panel* Editor::Scene = nullptr;
GameObject* Editor::CurrentSelectedGameObject = nullptr;

void Editor::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigWindowsMoveFromTitleBarOnly = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    auto hwnd = MainWindow::GetWindowHandler().HWND;
    MIKASA_ASSERT(hwnd != nullptr);
    ImGui_ImplWin32_Init(hwnd);

    auto rhi = (RHIDX11*) RenderDevice::RHI;
    ImGui_ImplDX11_Init(rhi->GetDevice(), rhi->GetDeviceContext());

    Menu = new MainMenuBar();

    Hierarchy = new HierarchyPanel();
    Hierarchy->Init();

    Inspector = new InspectorPanel();
    Inspector->Init();

    Game = new GamePanel();
    Game->Init();

    Scene = new ScenePanel();
    Scene->Init();
}


void Editor::UnInit()
{
    Hierarchy->UnInit();
    delete Hierarchy;
    Hierarchy = nullptr;

    Inspector->UnInit();
    delete Inspector;
    Inspector = nullptr;

    Game->UnInit();
    delete Game;
    Game = nullptr;

    Scene->UnInit();
    delete Scene;
    Scene = nullptr;

    delete Menu;
    Menu = nullptr;

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}


void Editor::StartFrame()
{
    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

/**
 * run on main thread.
 */
void Editor::Render()
{
    Menu->Render();
    Hierarchy->RenderWindow();
    Inspector->RenderWindow();
    Game->RenderWindow();
    Scene->RenderWindow();

    // imgui rendering
    ImGui::Render();

    // copy & push render data to render thread for rendering
    auto renderData = CopyDrawDataForRender(ImGui::GetDrawData());
    auto lambda = [=] ()
    {
        auto rtv = RenderDevice::RHI->GetBackBufferRTV();
        RenderDevice::RHI->OMSetRenderTarget(rtv);
        RenderDevice::RHI->ClearRenderTarget(rtv, Vector4f(0.2, 0.4, 0.6, 1.0));

        ImGui_ImplDX11_RenderDrawData(renderData.get());
        ReleaseDrawDataAfterRender(renderData);
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);

}


void Editor::EndFrame()
{

}

void Editor::DrawDemoWindow()
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }
}

std::shared_ptr<ImDrawData> Editor::CopyDrawDataForRender(const ImDrawData *data)
{
    auto clone = std::make_shared<ImDrawData>();
    clone->Valid = data->Valid;
    clone->CmdListsCount = data->CmdListsCount;
    clone->TotalIdxCount = data->TotalIdxCount;
    clone->TotalVtxCount = data->TotalVtxCount;
    for(auto drawList : data->CmdLists)
    {
        auto cloneDrawList = drawList->CloneOutput();
        clone->CmdLists.push_back(cloneDrawList);
    }
    clone->DisplayPos = data->DisplayPos;
    clone->DisplaySize = data->DisplaySize;
    clone->FramebufferScale = data->FramebufferScale;
    clone->OwnerViewport = data->OwnerViewport;

    return clone;
}

void Editor::ReleaseDrawDataAfterRender(const std::shared_ptr<ImDrawData> &data)
{
    for(auto drawList : data->CmdLists)
    {
        // a good example to explain how to debug memory leak using vs
        drawList->~ImDrawList();

        IM_FREE(drawList);
    }
    data->Clear();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool Editor::InstanceWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;
    return false;
}


