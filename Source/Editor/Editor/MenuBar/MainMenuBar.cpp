
#include "MainMenuBar.h"
#include "../Editor.h"
#include "imgui.h"

using namespace mikasa::Editor;


MainMenuBar::MainMenuBar()
{

}

void MainMenuBar::Render()
{
    if (ImGui::BeginMainMenuBar())
    {
        RenderView();
        ImGui::EndMainMenuBar();
    }
}

void MainMenuBar::RenderView()
{

    if (ImGui::BeginMenu("Panel"))
    {
        if (ImGui::MenuItem("Hierarchy", nullptr))
        {
            Editor::Hierarchy->Show();
        }
        if (ImGui::MenuItem("Game", nullptr))
        {
            Editor::Game->Show();
        }
        if (ImGui::MenuItem("Inspector", nullptr))
        {
            Editor::Inspector->Show();
        }
        if (ImGui::MenuItem("Scene", nullptr))
        {
            Editor::Scene->Show();
        }
        ImGui::EndMenu();
    }
}

