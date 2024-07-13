#pragma once

#include "../Panel.h"

namespace mikasa::Editor
{
    class InspectorPanel : public Panel
    {
    public:
        InspectorPanel();
        void Init() override;
        void UnInit() override;
    protected:
        void RenderContent() override;

    };
}
