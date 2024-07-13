#pragma once
#include "../Panel.h"

namespace mikasa::Editor
{
    class ScenePanel : public Panel
    {
    public:
        ScenePanel();
        void Init() override;
        void UnInit() override;

    protected:
        void RenderContent() override;

    };
}

