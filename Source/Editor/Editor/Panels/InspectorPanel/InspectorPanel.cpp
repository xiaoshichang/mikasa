
#include "InspectorPanel.h"
#include "../../Editor.h"
#include "Runtime/Foundation/Foundation.h"


using namespace mikasa::Editor;

InspectorPanel::InspectorPanel() : Panel("Inspector")
{

}


void InspectorPanel::Init()
{

}

void InspectorPanel::UnInit()
{

}

void InspectorPanel::HandleInput()
{

}

void InspectorPanel::RenderContent()
{
    if (Editor::CurrentSelectedGameObject == nullptr)
    {
        return;
    }

    RenderBasicInfo(Editor::CurrentSelectedGameObject);
    RenderTransform(Editor::CurrentSelectedGameObject);

}

void InspectorPanel::RenderBasicInfo(GameObject *go)
{
    ImGui::Separator();
    const auto& name = go->GetName();
    ImGui::Text("Name: %s", name.c_str());
}

void InspectorPanel::RenderTransform(GameObject *go)
{
    auto& transform = go->GetTransform();
    auto position = transform.GetPosition();
    auto p = position;
    auto rotation = transform.GetRotation().ToEuler();
    auto r = rotation;
    auto scale = transform.GetScale();
    auto s = scale;

    ImGui::Separator();
    ImGui::Text("Transform");
    auto positionChange = ImGui::DragFloat3("Position", position.data, 0.01f);
    auto rotationChange = ImGui::DragFloat3("Rotation", rotation.data, 0.01f);
    auto scaleChange = ImGui::DragFloat3("Scale", scale.data, 0.01f);

    if (positionChange && position != p)
    {
        transform.SetPosition(position);
    }
    if (rotationChange && rotation != r)
    {
        rotation.x = mikasa::Runtime::Foundation::Clamp(-PI / 2, PI / 2, rotation.x);
        transform.SetRotation(rotation.x, rotation.y, rotation.z);
    }
    if (scaleChange && scale != s)
    {
        transform.SetScale(scale);
    }
}





