#pragma once

#include "../../Panel.h"
#include "Runtime/Core/Scene/GameObject.h"

using namespace mikasa::Runtime::Core;

namespace mikasa::Editor
{
    class InspectorPanel : public Panel
    {
    public:
        InspectorPanel();
        void Init() override;
        void UnInit() override;
    protected:
        void HandleInput() override;
        void RenderContent() override;

    private:
        static void RenderBasicInfo(GameObject* go);
        static void RenderTransform(GameObject* go);

    };
}
