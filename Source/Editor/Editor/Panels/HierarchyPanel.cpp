
#include "HierarchyPanel.h"
#include "Runtime/Module/SceneModule/SceneModule.h"
#include "../Editor.h"

using namespace mikasa::Editor;
using namespace mikasa::Runtime::Module;

HierarchyPanel::HierarchyPanel() : Panel("Hierarchy")
{

}

void HierarchyPanel::Init() {

}

void HierarchyPanel::UnInit() {

}

void HierarchyPanel::RenderContent()
{
    auto scene = SceneModule::Current;
    auto gameObjects = scene->GetAllGameObjects();
    ImGuiTreeNodeFlags styleFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_Leaf;


    for (auto gameObject : gameObjects)
    {
        ImGuiTreeNodeFlags itemFlags = styleFlags;
        if (gameObject == Editor::CurrentSelectedGameObject)
        {
            itemFlags |= ImGuiTreeNodeFlags_Selected;
        }

        if (ImGui::TreeNodeEx(gameObject->GetName().c_str(), itemFlags))
        {
            if (ImGui::IsItemClicked())
            {
                Editor::CurrentSelectedGameObject = gameObject;
            }
            ImGui::TreePop();
        }
    }
}


