#pragma once

#include "../Panel.h"

namespace mikasa::Editor
{
    class HierarchyPanel : public Panel
    {
    public:
        HierarchyPanel();
        void Init() override;
        void UnInit() override;

    protected:
        void RenderContent() override;

    };
}

