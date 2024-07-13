
#include "Panel.h"

#include <utility>

using namespace mikasa::Editor;


void Panel::RenderWindow()
{
    if (!IsShow_)
    {
        return;
    }
    ImGui::Begin(WindowName_.c_str(), &IsShow_, WindowFlag_);
    RenderContent();
    ImGui::End();
}

Panel::Panel(std::string windowName)
    : WindowName_(std::move(windowName))
{
}
